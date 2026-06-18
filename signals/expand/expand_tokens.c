/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 00:00:00 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 22:46:47 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*process_word_token(t_shell *shell,
	t_token *current, t_token *prev)
{
	char	*new_val;

	new_val = process_expand(shell, current->value);
	if (new_val && *new_val == '\0' && !has_quotes(current->value))
	{
		if (prev != NULL && is_redirection(prev->token_type))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(current->value, STDERR_FILENO);
			ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
			shell->exit_code = 1;
			free(new_val);
			free_token_lst(shell->token);
			shell->token = NULL;
			return (NULL);
		}
		free(new_val);
		return (del_token_node(&shell->token, prev, current));
	}
	free(current->value);
	current->value = new_val;
	return (current);
}

void	expand_tokens(t_shell *shell)
{
	t_token	*current;
	t_token	*prev;
	t_token	*next;

	current = shell->token;
	prev = NULL;
	while (current != NULL)
	{
		if (current->token_type == WORD)
		{
			next = process_word_token(shell, current, prev);
			if (shell->token == NULL)
				return ;
			if (next != current)
			{
				current = next;
				continue ;
			}
		}
		prev = current;
		current = current->next;
	}
}
