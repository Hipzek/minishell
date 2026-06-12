/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:59:43 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/10 21:11:37 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Point de depart, : ls -l > out | wc -l
Donc la liste chainee est : [ls] -> [-l] -> [>] -> [out] -> [|] -> [wc] -> [-l]

Lecture de gauche a droite

Tri :
Creation de la Commande 1
ls (WORD) = Arg
-l (WORD) = Arg
NB: les redir se lisent tjs par paires donc redir + mot juste apres
> out (REDIR_OUT) = Redir
| (PIPE) = Donc stop, fin de la Commande 1 

Creation Commande 2
| (PIPE) est jete a la poubelle car il a fait son travail de separation
wc (WORD) = Arg
-l (WORD) = Arg

FIN de la liste

Par consequent de Bloc finale (cmd 1 et cmd 2)

Cette etape sert donc a extraire tout ce qui est "tuyauterie" (pipes, redir)
pour laisser les cmds parfaitements propres
*/

static int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL && token->token_type != PIPE)
	{
		if (is_redirection(token->token_type))
			token = token->next->next;
		else
		{
			count++;
			token = token->next;
		}
	}
	return (count);
}

static int	add_redir(t_redir **redir, t_token_type type,
	char *file, int heredoc_fd)
{
	t_redir	*new_node;
	t_redir	*last_node;

	new_node = ft_calloc(1, sizeof(t_redir));
	if (!new_node)
	{
		if (heredoc_fd >= 0)
			close(heredoc_fd);
		return (-1);
	}
	new_node->type = type;
	new_node->file = ft_strdup(file);
	if (!new_node->file)
	{
		if (heredoc_fd >= 0)
			close(heredoc_fd);
		free(new_node);
		return (-1);
	}
	new_node->heredoc_fd = heredoc_fd;
	if (*redir == NULL)
		*redir = new_node;
	else
	{
		last_node = *redir;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	return (0);
}

static int	fill_cmd_args(t_shell *shell, t_cmd *cmd, t_token **token)
{
	int	i;
	int	heredoc_fd;

	i = 0;
	while (*token != NULL && (*token)->token_type != PIPE)
	{
		if (is_redirection((*token)->token_type))
		{
			heredoc_fd = -1;
			if ((*token)->token_type == HEREDOC)
			{
				heredoc_fd = read_heredoc(shell, (*token)->next->value);
				if (heredoc_fd == -1)
					return (-1);
			}
			if (add_redir(&(cmd->redir), (*token)->token_type,
				(*token)->next->value, heredoc_fd) == -1)
			{
				if (heredoc_fd >= 0)
					close(heredoc_fd);
				return (-1);
			}
			*token = (*token)->next->next;
		}
		else
		{
			cmd->args[i] = ft_strdup((*token)->value);
			if (cmd->args[i] == NULL)
				return (-1);
			i++;
			*token = (*token)->next;
		}
	}
	cmd->args[i] = NULL;
	return (0);
}

static t_cmd	*parse_cmd(t_shell *shell, t_token **token)
{
	t_cmd	*cmd;
	int		argc;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	shell->cmd = cmd;
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
			return (NULL);
		}
		if (head == NULL)
		{
			head = new_cmd;
			tail = new_cmd;
		}
		else
		{
			tail->next = new_cmd;
			tail = new_cmd;
		}
	}
	return (head);
}
