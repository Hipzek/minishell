/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 21:58:05 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/14 17:10:14 by hbelleuv         ###   ########.fr       */
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
	if (shell->cmd != NULL)
	{
		free_cmd_lst(shell->cmd);
		shell->cmd = NULL;
	}
}

void	clean_and_exit(t_shell *shell, int exit_code)
{
	free_shell(shell);
	rl_clear_history();
	exit(exit_code);
}
