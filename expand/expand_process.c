/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 04:13:41 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 05:06:44 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_process_dollar_char(t_shell *shell, char *res,
	char *str, int *i)
{
	t_state	state;

	state = *(t_state *)(str + 256);
	if (str[*i + 1] == '\0' || str[*i + 1] == ' ' || str[*i + 1] == '\t')
	{
		res = ft_strjoin_char(res, str[*i]);
		(*i)++;
	}
	else if ((str[*i + 1] == '"' || str[*i + 1] == '\'') && state == NORMAL)
		(*i)++;
	else if (str[*i + 1] == '?')
		res = append_var_value(shell, res, str, i, state);
	else if (ft_isdigit(str[*i + 1]))
		*i += 2;
	else if (ft_isalpha(str[*i + 1]) || str[*i + 1] == '_')
		res = append_var_value(shell, res, str, i, state);
	else
	{
		res = ft_strjoin_char(res, str[*i]);
		(*i)++;
	}
	return (res);
}

static char	*process_expand(t_shell *shell, char *str)
{
	char	*res;
	t_state	state;
	int		i;

	res = ft_strdup("");
	state = NORMAL;
	i = 0;
	while (str[i])
	{
		ft_update_quote_state(str[i], &state);
		if (str[i] == '$' && state != IN_SQUOTE)
			res = ft_process_dollar_char(shell, res, str, &i);
		else
		{
			res = ft_strjoin_char(res, str[i]);
			i++;
		}
	}
	return (res);
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

static void	ft_handle_empty_expansion(t_shell *shell, t_token **token,
	t_token *prev, t_token **current)
{
	if (prev != NULL && is_redirection(prev->token_type))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd((*current)->value, STDERR_FILENO);
		ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
		shell->exit_code = 1;
		free_token_lst(*token);
		*token = NULL;
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
