/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 04:31:03 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 04:31:07 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_heredoc_fds(t_cmd *cmd)
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

int	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*name;

	if (!shell || !cmd || !cmd->args || !cmd->args[0])
		return (1);
	name = cmd->args[0];
	if (ft_strncmp(name, "echo", 5) == 0)
		return (ft_echo(shell, cmd));
	if (ft_strncmp(name, "cd", 3) == 0)
		return (ft_cd(shell, cmd));
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (ft_pwd(shell, cmd));
	if (ft_strncmp(name, "export", 7) == 0)
		return (ft_export(shell, cmd));
	if (ft_strncmp(name, "unset", 6) == 0)
		return (ft_unset(shell, cmd));
	if (ft_strncmp(name, "env", 4) == 0)
		return (ft_env(shell, cmd));
	if (ft_strncmp(name, "exit", 5) == 0)
		return (ft_exit(shell, cmd));
	return (-1);
}

/*
if (WIFEXITED(status)) //Terminaison classique (exit(0) ou exit(127))
else if (WIFSIGNALED(status)) //Terminaison forcee par un signal
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
			if (WIFEXITED(status))
				shell->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				shell->exit_code = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGQUIT)
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				else if (WTERMSIG(status) == SIGINT)
					printf("\n");
			}
		}
		wait_pid = waitpid(-1, &status, 0);
	}
}
