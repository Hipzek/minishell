/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 22:40:02 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/18 01:07:58 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*reduce_spaces(char *str)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			res = ft_strjoin_char(res, ' ');
		}
		else
		{
			res = ft_strjoin_char(res, str[i]);
			i++;
		}
	}
	return (res);
}

static void	advance_state(t_expctx *ctx)
{
	char	c;

	c = ctx->str[*(ctx->i)];
	if (c == '\'' && ctx->state == NORMAL)
		ctx->state = IN_SQUOTE;
	else if (c == '\'' && ctx->state == IN_SQUOTE)
		ctx->state = NORMAL;
	else if (c == '"' && ctx->state == NORMAL)
		ctx->state = IN_DQUOTE;
	else if (c == '"' && ctx->state == IN_DQUOTE)
		ctx->state = NORMAL;
}

static int	is_dollar_expandable(t_expctx *ctx)
{
	char	next;

	if (ctx->str[*(ctx->i)] != '$' || ctx->state == IN_SQUOTE)
		return (0);
	next = ctx->str[*(ctx->i) + 1];
	if (!next || next == ' ' || next == '\t' || next == '"' || next == '\'')
		return (0);
	if (ft_isdigit(next))
		return (-1);
	return (1);
}

static char	*process_char(t_shell *shell, char *res, t_expctx *ctx)
{
	char	*str;
	int		*i;
	int		ret;

	str = ctx->str;
	i = ctx->i;
	advance_state(ctx);
	ret = is_dollar_expandable(ctx);
	if (ret == 1)
		res = append_var_value(shell, res, ctx);
	else if (ret == -1)
		*i += 2;
	else if (str[*i] == '$' && ctx->state == NORMAL
		&& (str[*i + 1] == '"' || str[*i + 1] == '\''))
		(*i)++;
	else
		res = ft_strjoin_char(res, str[(*i)++]);
	return (res);
}

char	*process_expand(t_shell *shell, char *str)
{
	char		*res;
	t_expctx	ctx;
	int			i;

	res = ft_strdup("");
	i = 0;
	ctx.str = str;
	ctx.i = &i;
	ctx.state = NORMAL;
	while (str[i])
		res = process_char(shell, res, &ctx);
	return (res);
}
