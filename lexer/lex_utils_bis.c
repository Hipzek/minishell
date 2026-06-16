/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 00:55:02 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 00:55:05 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_append(t_struct_lex *lex)
{
	t_token	*new_node;

	if (!lex)
		return (1);
	if (ft_flush(lex))
		return (1);
	lex->start = -1;
	new_node = ft_new_node(">>", APPEND);
	if (!new_node)
		return (1);
	if (ft_add_back(&lex->head_lst, new_node))
		return (1);
	lex->i += 2;
	return (0);
}

int	ft_heredoc(t_struct_lex *lex)
{
	t_token	*new_node;

	if (!lex)
		return (1);
	if (ft_flush(lex))
		return (1);
	lex->start = -1;
	new_node = ft_new_node("<<", HEREDOC);
	if (!new_node)
		return (1);
	if (ft_add_back(&lex->head_lst, new_node))
		return (1);
	lex->i += 2;
	return (0);
}

int	ft_redir_out(t_struct_lex *lex)
{
	t_token	*new_node;

	if (!lex)
		return (1);
	if (ft_flush(lex))
		return (1);
	lex->start = -1;
	new_node = ft_new_node(">", REDIR_OUT);
	if (!new_node)
		return (1);
	if (ft_add_back(&lex->head_lst, new_node))
		return (1);
	lex->i += 1;
	return (0);
}

int	ft_redir_in(t_struct_lex *lex)
{
	t_token	*new_node;

	if (!lex)
		return (1);
	if (ft_flush(lex))
		return (1);
	lex->start = -1;
	new_node = ft_new_node("<", REDIR_IN);
	if (!new_node)
		return (1);
	if (ft_add_back(&lex->head_lst, new_node))
		return (1);
	lex->i += 1;
	return (0);
}
