/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:15:27 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/04/27 16:14:09 by hbelleuv         ###   ########.fr       */
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
- Si non cherchez le $PATH et appelez execve($PATH, cmd->args, envp)

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

int	exec_pipeline(t_shell *shell)
{
	t_cmd	*current;
	int		pipe_fd[2];
	int		relay_fd;
	pid_t	pid;

	pid = -1;
	relay_fd = -1;
	current = shell->cmd;
	if (current->next == NULL && is_builtin(current))
		return (exec_builtin(current, shell->envp));
	while (current != NULL)
	{
		if (current->next != NULL)
			pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
			exec_child(current, relay_fd, pipe_fd, shell->envp);
		if (relay_fd != -1)
			close(relay_fd);
		if (current->next != NULL)
		{
			close(pipe_fd[1]);
			relay_fd = pipe_fd[0];
		}
		current = current->next;
	}
	return (wait_pipeline(shell, pid));
}

void	exec_child(t_cmd *cmd, int relay_fd, int pipe_fd[2], char **envp)
{
	int	ret;

	if (relay_fd != -1)
	{
		dup2(relay_fd, STDIN_FILENO);
		close(relay_fd);
	}
	if (cmd->next != NULL)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	apply_redir(cmd);
	if (is_builtin(cmd))
	{
		ret = exec_builtin(cmd, envp);
		exit(ret);
	}
	if (cmd->args == NULL || cmd->args[0] == NULL)
	{
		// garbage collector
		exit(0);
	}
	cmd->path = path(cmd->args[0], envp);
	if (cmd->path == NULL)
	{
		ft_putstr_fd(cmd->args, 2);
		ft_putstr_fd(": command not found\n", 2);
		// garbage collector;
		exit(127);
	}
	execve(cmd->path, cmd->args, envp);
	perror(cmd->args);
	//garbage collector
	exit(126);
}
