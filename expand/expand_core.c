/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 21:55:00 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 21:55:00 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*process_expand(t_shell *shell, char *str)
{
	t_expand	exp;

	expand_init(&exp, shell, str);
	while (exp.str[exp.i])
		process_char(&exp);
	return (exp.res);
}
