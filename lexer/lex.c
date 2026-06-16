/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 01:02:43 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 01:03:34 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_act_emit_pipe(t_struct_lex *lex)
{
	t_token	*new_node;

	if (!lex)
		return (1);
	if (ft_flush(lex))
		return (1);
	lex->start = -1;
	new_node = ft_new_node("|", PIPE);
	if (!new_node)
		return (1);
	if (ft_add_back(&lex->head_lst, new_node))
		return (1);
	lex->i += 1;
	return (0);
}

int	ft_act_flush(t_struct_lex *lex)
{
	if (!lex)
		return (1);
	if (ft_flush(lex))
		return (1);
	lex->start = -1;
	lex->i += 1;
	return (0);
}

int	ft_act_emit_redir(t_struct_lex *lex)
{
	char	redir;
	char	next;

	if (!lex)
		return (1);
	redir = lex->raw[lex->i];
	next = lex->raw[lex->i + 1];
	if (redir == '>' && next == '>')
		return (ft_append(lex));
	else if (redir == '<' && next == '<')
		return (ft_heredoc(lex));
	else if (redir == '<')
		return (ft_redir_in(lex));
	else if (redir == '>')
		return (ft_redir_out(lex));
	return (1);
}

int	ft_flush(t_struct_lex *lex)
{
	char	*value;
	t_token	*new_node;

	if (!lex)
		return (1);
	if (lex->start == -1)
		return (0);
	value = ft_substr(lex->raw, lex->start, (lex->i - lex->start));
	if (!value)
		return (1);
	new_node = ft_new_node(value, WORD);
	free(value);
	if (!new_node)
		return (1);
	if (ft_add_back(&lex->head_lst, new_node))
	{
		free_token_lst(new_node);
		return (1);
	}
	return (0);
}
