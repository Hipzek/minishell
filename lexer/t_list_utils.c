/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:06:51 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 01:10:30 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_token_type_name(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

int	ft_print_link_c(t_token *head_lst)
{
	t_token	*current;

	if (!head_lst)
		return (1);
	current = head_lst;
	while (current != NULL)
	{
		printf("[\"%s\" | %s] ->", current->value,
			ft_token_type_name(current->token_type));
		current = current->next;
	}
	printf("NULL\n");
	return (0);
}
