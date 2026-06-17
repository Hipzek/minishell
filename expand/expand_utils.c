/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 21:55:00 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 21:55:00 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*del_token_node(t_token **head, t_token *prev, t_token *to_del)
{
	t_token	*next_node;

	next_node = to_del->next;
	if (prev == NULL)
		*head = next_node;
	else
		prev->next = next_node;
	if (to_del->value)
		free(to_del->value);
	free(to_del);
	return (next_node);
}
