/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_lex_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:04:14 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/13 14:04:19 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_do_lex(t_struct_lex *lex)
{
	t_state		before_state;
	t_state		after_state;
	t_char_type	type;
	t_action	action;
	t_state		state_table[3][6];
	t_action	action_table[3][6];

	ft_fill_state_table(state_table);
	ft_fill_action_table(action_table);
	while (lex->raw[lex->i])
	{
		before_state = lex->state;
		type = ft_get_char_type(lex->raw[lex->i]);
		after_state = state_table[before_state][type];
		action = action_table[before_state][type];
		if (ft_exec_action(lex, action))
			return (1);
		lex->state = after_state;
	}
	if (ft_flush(lex))
		return (1);
	return (0);
}
