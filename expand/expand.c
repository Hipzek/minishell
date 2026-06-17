/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:55:49 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 22:16:26 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_handle_spaces(char *res, char *str, int *i)
{
	int	space_count;

	space_count = 0;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '	'))
	{
		space_count++;
		(*i)++;
	}
	if (space_count > 0)
		res = ft_strjoin_char(res, ' ');
	return (res);
}

static char	*reduce_spaces(char *str)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '	')
			res = ft_handle_spaces(res, str, &i);
		else
		{
			res = ft_strjoin_char(res, str[i]);
			i++;
		}
	}
	return (res);
}

void	ft_append_dollar_expansion(t_expand *exp)
{
	char	*var_name;
	char	*var_value;
	char	*processed_value;
	char	*tmp;
	int		start;

	exp->i++;
	if (exp->str[exp->i] == '?')
	{
		tmp = exp->res;
		var_value = ft_itoa(exp->shell->exit_code);
		exp->res = ft_strjoin(tmp, var_value);
		free(var_value);
		free(tmp);
		exp->i++;
		return ;
	}
	start = exp->i;
	while (exp->str[exp->i] && (ft_isalnum(exp->str[exp->i])
			|| exp->str[exp->i] == '_'))
		exp->i++;
	var_name = ft_substr(exp->str, start, exp->i - start);
	var_value = get_env(exp->shell, var_name);
	free(var_name);
	if (var_value == NULL)
		return ;
	tmp = exp->res;
	if (exp->state == NORMAL)
	{
		processed_value = reduce_spaces(var_value);
		exp->res = ft_strjoin(tmp, processed_value);
		free(processed_value);
	}
	else
		exp->res = ft_strjoin(tmp, var_value);
	free(tmp);
}

int	is_valid_dollar(char c)
{
	if (c == '\0' || c == ' ' || c == '\t')
		return (0);
	if (c == '"' || c == '\'')
		return (0);
	return (1);
}

void	ft_update_quote_state(char c, t_state *state)
{
	if (c == '\'' && *state == NORMAL)
		*state = IN_SQUOTE;
	else if (c == '\'' && *state == IN_SQUOTE)
		*state = NORMAL;
	else if (c == '"' && *state == NORMAL)
		*state = IN_DQUOTE;
	else if (c == '"' && *state == IN_DQUOTE)
		*state = NORMAL;
}
