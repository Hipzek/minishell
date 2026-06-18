/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:55:49 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 22:46:32 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*expand_exit_code(t_shell *shell, char *res, t_expctx *ctx)
{
	char	*var_value;
	char	*tmp;

	tmp = res;
	*(ctx->i) += 1;
	var_value = ft_itoa(shell->exit_code);
	res = ft_strjoin(tmp, var_value);
	free(var_value);
	free(tmp);
	return (res);
}

static char	*expand_env_var(t_shell *shell, char *res, t_expctx *ctx)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;
	int		start;

	tmp = res;
	start = *(ctx->i);
	while (ctx->str[*(ctx->i)]
		&& (ft_isalnum(ctx->str[*(ctx->i)]) || ctx->str[*(ctx->i)] == '_'))
		(*(ctx->i))++;
	var_name = ft_substr(ctx->str, start, *(ctx->i) - start);
	var_value = get_env(shell, var_name);
	free(var_name);
	if (var_value != NULL)
	{
		if (ctx->state == NORMAL)
			var_value = reduce_spaces(var_value);
		res = ft_strjoin(tmp, var_value);
		if (ctx->state == NORMAL)
			free(var_value);
		free(tmp);
	}
	else
		res = tmp;
	return (res);
}

char	*append_var_value(t_shell *shell, char *res, t_expctx *ctx)
{
	(*(ctx->i))++;
	if (ctx->str[*(ctx->i)] == '?')
		return (expand_exit_code(shell, res, ctx));
	return (expand_env_var(shell, res, ctx));
}

int	is_valid_dollar(char c)
{
	if (c == '\0' || c == ' ' || c == '\t')
		return (0);
	if (c == '"' || c == '\'')
		return (0);
	return (1);
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
