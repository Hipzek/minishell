/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 04:50:50 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 04:50:53 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Revoir stat :
...
*/

static void	ft_setup_child_io(t_cmd *cmd, int relay_fd, int pipe_fd[2])
{
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
}

static void	ft_check_empty_command(t_shell *shell, t_cmd *cmd)
{
	if (cmd->args == NULL || cmd->args[0] == NULL)
		clean_and_exit(shell, 0);
	if (cmd->args[0][0] == '\0')
	{
		ft_putstr_fd("minishell: : command not found\n", STDERR_FILENO);
		clean_and_exit(shell, 127);
	}
}

static void	ft_check_absolute_path(t_shell *shell, t_cmd *cmd)
{
	struct stat	path_stat;

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

static void	ft_resolve_command_path(t_shell *shell, t_cmd *cmd)
{
	if (ft_strchr(cmd->args[0], '/') != NULL)
		ft_check_absolute_path(shell, cmd);
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
}

void	exec_child(t_shell *shell, t_cmd *cmd, int relay_fd, int pipe_fd[2])
{
	int	ret;

	setup_child_signal();
	ft_setup_child_io(cmd, relay_fd, pipe_fd);
	apply_redir(shell, cmd);
	if (is_builtin(cmd))
	{
		ret = exec_builtin(shell, cmd);
		clean_and_exit(shell, ret);
	}
	ft_check_empty_command(shell, cmd);
	ft_resolve_command_path(shell, cmd);
	execve(cmd->path, cmd->args, shell->env);
	perror(cmd->args[0]);
	clean_and_exit(shell, 126);
}
