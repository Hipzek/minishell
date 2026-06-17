/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 03:30:16 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 03:30:20 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_free_shell_resources(t_shell *shell)
{
	if (shell->env != NULL)
	{
		free_double_tab(shell->env);
		shell->env = NULL;
	}
	if (shell->token != NULL)
	{
		free_token_lst(shell->token);
		shell->token = NULL;
	}
	if (shell->cmd != NULL)
	{
		free_cmd_lst(shell->cmd);
		shell->cmd = NULL;
	}
}

static void	ft_close_shell_fds(t_shell *shell)
{
	if (shell->saved_stdin != -1)
	{
		close(shell->saved_stdin);
		shell->saved_stdin = -1;
	}
	if (shell->saved_stdout != -1)
	{
		close(shell->saved_stdout);
		shell->saved_stdout = -1;
	}
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	ft_free_shell_resources(shell);
	ft_close_shell_fds(shell);
}
