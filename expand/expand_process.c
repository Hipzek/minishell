/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 04:13:41 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 20:03:57 by hbelleuv         ###   ########.fr       */
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

static void	process_dollar_char(t_expand *exp)
{
	char	next;

	next = exp->str[exp->i + 1];
	process_dollar_special(exp, next);
}

static void	expand_init(t_expand *exp, t_shell *shell, char *str)
{
	exp->shell = shell;
	exp->res = ft_strdup("");
	exp->state = NORMAL;
	exp->str = str;
	exp->i = 0;
}

static void	process_char(t_expand *exp)
{
	ft_update_quote_state(exp->str[exp->i], &exp->state);
	if (exp->str[exp->i] == '$' && exp->state != IN_SQUOTE)
		process_dollar_char(exp);
	else
	{
		exp->res = ft_strjoin_char(exp->res, exp->str[exp->i]);
		exp->i++;
	}
}

static char	*process_expand(t_shell *shell, char *str)
{
	t_expand	exp;

	expand_init(&exp, shell, str);
	while (exp.str[exp.i])
		process_char(&exp);
	return (exp.res);
}

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

static void	ambiguous_redirect(t_shell *shell, t_token **token,
	t_token *current)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(current->value, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
	shell->exit_code = 1;
	free_token_lst(*token);
	*token = NULL;
}

static void	ft_handle_empty_expansion(t_shell *shell, t_token **token,
	t_token *prev, t_token **current)
{
	if (prev != NULL && is_redirection(prev->token_type))
	{
		ambiguous_redirect(shell, token, *current);
		return ;
	}
	*current = del_token_node(token, prev, *current);
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
				ft_handle_empty_expansion(shell, &shell->token, prev, &current);
				continue ;
			}
			free(current->value);
			current->value = new_val;
		}
		prev = current;
		current = current->next;
	}
}
