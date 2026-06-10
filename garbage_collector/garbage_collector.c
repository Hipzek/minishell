/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 21:58:05 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/10 18:49:43 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_double_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	free_redir_lst(t_redir *redir)
{
	t_redir	*tmp;

	while (redir != NULL)
	{
		tmp = redir->next;
		if (redir->heredoc_fd >= 0)
		{
			close(redir->heredoc_fd);
			redir->heredoc_fd = -1;
		}
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_cmd_lst(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd != NULL)
	{
		tmp = cmd->next;
		if (cmd->args)
			free_double_tab(cmd->args);
		if (cmd->path)
			free(cmd->path);
		if (cmd->redir)
			free_redir_lst(cmd->redir);
		free(cmd);
		cmd = tmp;
	}
}

void	free_token_lst(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->value)
			free(token->value);
		free(token);
		token = tmp;
	}
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
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

void	clean_and_exit(t_shell *shell, int exit_code)
{
	if (shell->saved_stdin > 2)
	{
		close(shell->saved_stdin);
		shell->saved_stdin = -1;
	}
	if (shell->saved_stdout > 2)
	{
		close(shell->saved_stdout);
		shell->saved_stdout = -1;
	}
	free_shell(shell);
	rl_clear_history();
	exit(exit_code);
}
