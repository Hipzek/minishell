/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 01:43:42 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 21:55:00 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*parse_cmd(t_shell *shell, t_token **token)
{
	t_cmd	*cmd;
	int		argc;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	argc = count_args(*token);
	cmd->args = ft_calloc(argc + 1, sizeof(char *));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	if (fill_cmd_args(shell, cmd, token) == -1)
	{
		free_cmd_lst(cmd);
		return (NULL);
	}
	if (*token != NULL && (*token)->token_type == PIPE)
		*token = (*token)->next;
	return (cmd);
}

static void	ft_add_cmd_to_list(t_cmd **head, t_cmd **tail, t_cmd *new_cmd)
{
	if (*head == NULL)
	{
		*head = new_cmd;
		*tail = new_cmd;
	}
	else
	{
		(*tail)->next = new_cmd;
		*tail = new_cmd;
	}
}

t_cmd	*cmd_table(t_shell *shell)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*new_cmd;
	t_token	*tok;

	head = NULL;
	tail = NULL;
	tok = shell->token;
	while (tok != NULL)
	{
		new_cmd = parse_cmd(shell, &tok);
		if (new_cmd == NULL)
		{
			free_cmd_lst(head);
			shell->cmd = NULL;
			return (NULL);
		}
		ft_add_cmd_to_list(&head, &tail, new_cmd);
	}
	shell->cmd = head;
	return (head);
}
