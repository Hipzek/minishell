/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:59:43 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/04/26 16:12:37 by hbelleuv         ###   ########.fr       */
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
	while (token != NULL && token->type != PIPE)
	{
		if (is_redirection(token->type))
			token = token->next->next;
		else
		{
			count++;
			token = token->next;
		}
	}
	return (count);
}

static void	add_redir(t_redir **redir, t_token_type type, char *file)
{
	t_redir	*new_node;
	t_redir	*last_node;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return ;
	new_node->type = type;
	new_node->file = ft_strdup(file);
	new_node->next = NULL;
	if (*redir == NULL)
		*redir = new_node;
	else
	{
		last_node = *redir;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}

static void	fill_cmd_args(t_cmd *cmd, t_token **token)
{
	int	i;

	i = 0;
	while (*token != NULL && (*token)->type != PIPE)
	{
		if (is_redirection((*token)->type))
		{
			add_redir(&(cmd->redir), (*token)->type, (*token)->next->value);
			*token = (*token)->next->next;
		}
		else
		{
			cmd->args[i] = ft_strdup((*token)->value);
			i++;
			*token = (*token)->next;
		}
	}
	cmd->args[i] = NULL;
}

static t_cmd	*parse_cmd(t_token **token)
{
	t_cmd	*cmd;
	int		argc;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->redir = NULL;
	cmd->next = NULL;
	argc = count_args(*token);
	cmd->args = malloc(sizeof(char *) * (argc + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	fill_cmd_args(cmd, token);
	if (*token != NULL && (*token)->type == PIPE)
		*token = (*token)->next;
	return (cmd);
}

t_cmd	*cmd_table(t_token *token)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*new_cmd;

	head = NULL;
	tail = NULL;
	while (token != NULL)
	{
		new_cmd = parse_cmd(&token);
		if (new_cmd == NULL)
			break ;
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
