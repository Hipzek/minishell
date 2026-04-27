/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:11:47 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/04/27 16:34:49 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	apply_redir(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redir;
	while (redir != NULL)
	{
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
			fd = open(redir->file, O_RDONLY);
		else if (redir->type == REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror(redir->file);
			// garbage collector
			exit(1);
		}
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
			dup2(fd, STDIN_FILENO);
		else if (redir->type == REDIR_OUT || redir->type == APPEND)
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
}

int	is_builtin(t_cmd *cmd)
{
	char	*name;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	name = cmd->args[0];
	if (ft_strncmp(name, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(name, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(name, "env", 4) == 0)
		return (1);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, char **envp)
{
	char	*name;

	name = cmd->args[0];
	if (ft_strncmp(name, "echo", 5) == 0)
		return (ft_echo(cmd->args));
	if (ft_strncmp(name, "cd", 3) == 0)
		return (ft_cd(cmd->args, envp));
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (ft_pwd(cmd->args, envp));
	if (ft_strncmp(name, "export", 7) == 0)
		return (ft_export(cmd->args, envp));
	if (ft_strncmp(name, "unset", 6) == 0)
		return (ft_unset(cmd->args, envp));
	if (ft_strncmp(name, "env", 4) == 0)
		return (ft_env(cmd->args, envp));
	if (ft_strncmp(name, "exit", 5) == 0)
		return (ft_exit(cmd->args, envp));
	return (0);
}

/*
OBJECTIF :
--> Recup tous les processus enfants pour eviter processus "zombies"
--> Isoler statut du 1er processus pour mettre a jour shell->exit_code
*/

void	wait_pipeline(t_shell *shell, pid_t last_pid)
{
	int		status;
	pid_t	wait_pid;

	wait_pid = waitpid(-1, &status, 0);
	while (wait_pid > 0)
	{
		if (wait_pid == last_pid)
		{
			if (WIFEXITED(status)) //Terminaison classique (exit(0) ou exit(127))
				shell->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status)) //Terminaison forcee par un signal
			{
				shell->exit_code = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGQUIT)
					printf("Quit (core dumped)\n");
				else if (WTERMSIG(status) == SIGINT)
					printf("\n");
			}
		}
		wait_pid = waitpid(-1, &status, 0);
	}
}
