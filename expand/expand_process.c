/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 04:13:41 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 22:19:57 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	process_dollar_special(t_expand *exp, char next)
{
	if (next == '\0' || next == ' ' || next == '\t')
	{
		exp->res = ft_strjoin_char(exp->res, exp->str[exp->i]);
		exp->i++;
	}
	else if ((next == '"' || next == '\'') && exp->state == NORMAL)
		exp->i++;
	else if (next == '?' || ft_isalpha(next) || next == '_')
		ft_append_dollar_expansion(exp);
	else if (ft_isdigit(next))
		exp->i += 2;
	else
	{
		exp->res = ft_strjoin_char(exp->res, exp->str[exp->i]);
		exp->i++;
	}
}

void	process_dollar_char(t_expand *exp)
{
	char	next;

	next = exp->str[exp->i + 1];
	process_dollar_special(exp, next);
}

static void	ambiguous_redirect_err(t_shell *shell, t_token *current)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(current->value, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect", STDERR_FILENO);
	shell->exit_code = 1;
	free_token_lst(shell->token);
	shell->token = NULL;
}

void	expand_tokens(t_shell *shell)
{
	t_token	*current;
	t_token	*prev;
	char	*new_val;

	current = shell->token;
	prev = NULL;
	while (current != NULL)
	{
		if (current->token_type == WORD)
		{
			new_val = process_expand(shell, current->value);
			if (new_val && *new_val == '\0' && !has_quotes(current->value))
			{
				if (prev != NULL && is_redirection(prev->token_type))
				{
					ambiguous_redirect_err(shell, current);
					return ;
				}
				current = del_token_node(&shell->token, prev, current);
				continue ;
			}
			free(current->value);
			current->value = new_val;
		}
		prev = current;
		current = current->next;
	}
}
