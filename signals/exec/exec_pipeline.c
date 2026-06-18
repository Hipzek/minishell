/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:15:27 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 22:39:03 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	exec_single_builtin(t_shell *shell, t_cmd *cmd)
{
	if (cmd->redir != NULL)
	{
		if (apply_redir_parent(shell, cmd) != 0)
		{
			dup2(shell->saved_stdin, STDIN_FILENO);
			dup2(shell->saved_stdout, STDOUT_FILENO);
			close_heredoc_fds(cmd);
			return (1);
		}
	}
	shell->exit_code = exec_builtin(shell, cmd);
	dup2(shell->saved_stdin, STDIN_FILENO);
	dup2(shell->saved_stdout, STDOUT_FILENO);
	close_heredoc_fds(cmd);
	return (shell->exit_code);
}

static pid_t	do_fork(t_shell *shell, t_cmd *current,
	int relay_fd, int pipe_fd[2])
{
	pid_t	pid;

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
	}
	else if (pid == 0)
		exec_child(shell, current, relay_fd, pipe_fd);
	return (pid);
}

static int	pipe_one(t_shell *shell, t_cmd *current,
	int *relay_fd, int pipe_fd[2])
{
	pid_t	pid;

	if (current->next != NULL && pipe(pipe_fd) == -1)
	{
		perror("pipe");
		if (*relay_fd != -1)
			close(*relay_fd);
		return (-1);
	}
	pid = do_fork(shell, current, *relay_fd, pipe_fd);
	if (pid == -1)
		return (-1);
	close_heredoc_fds(current);
	if (current->next != NULL)
	{
		close(pipe_fd[1]);
		if (*relay_fd != -1)
			close(*relay_fd);
		*relay_fd = pipe_fd[0];
	}
	return (pid);
}

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
		return (exec_single_builtin(shell, current));
	while (current != NULL)
	{
		pid = pipe_one(shell, current, &relay_fd, pipe_fd);
		if (pid == -1)
			return (1);
		current = current->next;
	}
	if (relay_fd != -1)
		close(relay_fd);
	wait_pipeline(shell, pid);
	return (shell->exit_code);
}
