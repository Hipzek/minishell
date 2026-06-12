/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:15:27 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/10 18:55:57 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Pipes → Redirections → Execve

IF il y a 1 seule cmd, IF c')est un built-in qui 
modifie l'etat du shell (cd, export, unset, exit)
--> executer directement dans le processus parent 
sans jamais appeler fork() ou pipe()
CAR si fork() l'enfant va changer de dossier (ex : avec cd) mais pas le parent

--- BOUCLE PIPELINE (Parent) ---
Creation d'un fd_relay (Pour relier les cmds entre elles)
Pour chaque cmd :

1. IF ce n'est pas la derniere cmd (while cmd->next != NULL),
creer un nouevau tuyau (pipe(pipefd))

2. Appeler fork() pour creer l'enfant

3. Dans le parent, apres fork() :
- Fermer l'ecriture du nouveau tuyau (close(pipefd)),
sinon les cmds resteront bloquees en attendant EOF
- Fermer l'ancien relay_fd, s'il existe
- Mettre a jour relay_fd = pipefd pour que la prochaine
cmd puisse lire ce que celle a ecrit

--- Processus enfant (fork() == 0) ---

IF relay_fd existe alors : dup2(relay_fd, STDIN_FILENO)
			(le tuyau remplace le clavier)

IF il y a une cmd suivante mettre mettre tuyau actuel sur sortie standard :
dup2(pipefd, STDOUT_FILENO) (le tuyau remplace l'ecran)

Fermer ensuite tous les pipes ouvert car dup2 a deja fait le relai

--- Redirections ---

Parcourir cmd->redir
- REDIR_IN (<) : fd = open(file, O_RDONLY) (Lecture seule)
  		--> Puis dup2(fd, STDIN_FILENO).
- REDIR_OUT (>) : fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)
		(Écriture, Création si inexistant, Remplacement/Troncature si existant)
  		--> Puis dup2(fd, STDOUT_FILENO).
- APPEND (>>) : fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644) 
		(Écriture, Création si inexistant, Ajout à la fin si existant)
  		--> Puis dup2(fd, STDOUT_FILENO).
IF un open() echoue affichez une erreur (perror) et exit(1)
Fermer le fd renvoye par open apres dup2

--- Execution ---

Verif si la cmd est built-in :

- Si oui lancez la fonction en C puis appelez exit(code_de_retour) apres
- Si non cherchez le $PATH et appelez execve($PATH, cmd->args, env)

--- Attente ---
 Le parent doit attendre que tous les enfants soient termines
 --> boucle de waitpid(-1, &status, 0) 
CAR sinon avec 1 seul waitpid les autres enfants 
deviendront des porcessus zombies

Astuce : pour cela capturer le statut PID du dernier
--> On utilisant les macros : WIFEXITED et WEXITSTATUS
(ou WIFSIGNALED si la commande a été tuée par un signal)
*/

#include "../includes/minishell.h"

static void	close_heredoc_fds(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir != NULL)
	{
		if (redir->type == HEREDOC && redir->heredoc_fd >= 0)
		{
			close(redir->heredoc_fd);
			redir->heredoc_fd = -1;
		}
		redir = redir->next;
	}
}

// TODO : SI UNE SEULE FONCTION -> DANS PROCESS PARENT

int	exec_pipeline(t_shell *shell)
{
	t_cmd	*current;
	int		pipe_fd[2];
	int		relay_fd;
	pid_t	pid;

	pipe_fd[0] = -1;
	pipe_fd[1] = 1;
	pid = -1;
	relay_fd = -1;
	current = shell->cmd;
	if (current->next == NULL && is_builtin(current))
	{
		if (current->redir != NULL)
		{
			// TODO : A VERIFIER SI BESOIN DE DUP2 SI TRAITEMENT REDIRECTION ECHOUE
			if (apply_redir_parent(shell, current) != 0)
			{
				dup2(shell->saved_stdin, STDIN_FILENO);
				dup2(shell->saved_stdout, STDOUT_FILENO);
				close_heredoc_fds(current);
				return (1);
			}
		}
		shell->exit_code = exec_builtin(shell, current);
		dup2(shell->saved_stdin, STDIN_FILENO);
		dup2(shell->saved_stdout, STDOUT_FILENO);
		close_heredoc_fds(current);
		printf("CURRENT CMD \n");
		ft_print_cmd(current);
		// close(shell->saved_stdin);
		// close(shell->saved_stdout);
		printf("INFD = %d || OUTFD = %d\n", shell->saved_stdin, shell->saved_stdout);
		return (shell->exit_code);
	}
	while (current != NULL)
	{
		// POURQUOI PAS DE REGLE SI C'EST PAS LE DERNIER
		if (current->next != NULL)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				if (relay_fd != -1)
					close(relay_fd);
				return (1);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			if (relay_fd != -1)
				close(relay_fd);
			if (current->next != NULL)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			return (1);
		}
		if (pid == 0)
		{
			exec_child(shell, current, relay_fd, pipe_fd);
		}
		close_heredoc_fds(current);
		if (current->next != NULL)
		{
			close(pipe_fd[1]);
			if (relay_fd != -1)
				close(relay_fd);
			relay_fd = pipe_fd[0];
		}
		current = current->next;
	}
	if (relay_fd != -1)
		close(relay_fd);
	wait_pipeline(shell, pid);
	return (shell->exit_code);
}

/*
Revoir stat :
...
*/
void	exec_child(t_shell *shell, t_cmd *cmd, int relay_fd, int pipe_fd[2])
{
	int			ret;
	struct stat	path_stat;

	//close(shell->saved_stdin);
	//close(shell->saved_stdout);
	setup_child_signal();
	// printf("IN CHILD\n");
	// printf("PIPE[0] = %d || PIPE[1] = %d\n", pipe_fd[0], pipe_fd[1]);
	// RELAY FD SERT A RIEN PARCE QUE TOUJOURS A -1, AUCUN SET AVANT
	if (relay_fd != -1)
	{
		dup2(relay_fd, STDIN_FILENO);
		close(relay_fd);
	}

	// SI PAS LA DERNIERE COMMANDE
	if (cmd->next != NULL)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}	

	// TRAITE TOUTE LA LISTE DE REDIRECTION
	apply_redir(shell, cmd);
	if (is_builtin(cmd))
	{
		ret = exec_builtin(shell, cmd);
		printf("BEFORRRRRRRRRRRRRRRE\n");
		clean_and_exit(shell, ret);
		printf("AFTERRRRRRRRRRRRRRRRR\n");

	}
	if (cmd->args == NULL || cmd->args[0] == NULL)
		clean_and_exit(shell, 0);
	if (ft_strchr(cmd->args[0], '/') != NULL )
	{
		if (access(cmd->args[0], F_OK) == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			clean_and_exit(shell, 127);
		}
		if (stat(cmd->args[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			clean_and_exit(shell, 126);
		}
		if (access(cmd->args[0], X_OK) == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			clean_and_exit(shell, 126);
		}
		cmd->path = ft_strdup(cmd->args[0]);
	}
	else
	{
		cmd->path = path(cmd->args[0], shell->env);
		if (cmd->path == NULL)
		{
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			clean_and_exit(shell, 127);
		}
	}
	// ft_print_cmd(cmd);
	execve(cmd->path, cmd->args, shell->env);
	perror(cmd->args[0]);
	clean_and_exit(shell, 126);
}
