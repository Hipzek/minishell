/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:06:51 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/14 17:13:34 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_new_node(char *value_str, t_token_type type)
{
	t_token	*new;

	if (!value_str)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value_str);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->token_type = type;
	new->next = NULL;
	return (new);
}

int	ft_add_back(t_token **head_lst, t_token *new)
{
	t_token	*current;

	if (!head_lst || !new)
		return (1);
	if ((*head_lst) == NULL)
		return ((*head_lst) = new, 0);
	if (!(current = ft_found_last_lst(*head_lst)))
		return (1);
	current->next = new;
	return (0);
}

int	ft_count_node_in_lst(t_token *head_lst)
{
	t_token	*current;
	int		count;

	if (!head_lst)
		return (-1);
	current = head_lst;
	count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_token	*ft_found_last_lst(t_token *head_lst)
{
	t_token	*current;

	if (!head_lst)
		return (NULL);
	current = head_lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

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
