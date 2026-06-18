/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 00:00:00 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	warn_eof(char *delim)
{
	ft_putstr_fd("minishell: warning: here-document delimited", STDERR_FILENO);
	ft_putstr_fd("by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delim, STDERR_FILENO);
	ft_putstr_fd("`)", STDERR_FILENO);
}

static int	is_expandable(char *str, int i)
{
	return (str[i] == '$' && (str[i + 1] == '?'
			|| ft_isalpha(str[i + 1]) || str[i + 1] == '_'));
}

static char	*expand_heredoc_line(t_shell *shell, char *str)
{
	char		*res;
	t_expctx	ctx;
	int			i;

	res = ft_strdup("");
	if (!str || !res)
		return (res);
	i = 0;
	ctx.str = str;
	ctx.i = &i;
	ctx.state = NORMAL;
	while (str[i])
	{
		if (is_expandable(str, i))
			res = append_var_value(shell, res, &ctx);
		else if (str[i] == '$' && ft_isdigit(str[i + 1]))
			i += 2;
		else
		{
			res = ft_strjoin_char(res, str[i]);
			i++;
		}
	}
	free(str);
	return (res);
}

static int	handle_hd_line(t_shell *shell, t_hd_ctx *ctx, char *line)
{
	if (g_sig == SIGINT)
		return (free(line), 1);
	if (line == NULL)
	{
		if (g_sig != SIGINT)
			warn_eof(ctx->delim);
		return (1);
	}
	if (ft_strcmp(line, ctx->delim) == 0)
		return (free(line), 1);
	if (ctx->expand)
		line = expand_heredoc_line(shell, line);
	ft_putendl_fd(line, ctx->fd[1]);
	free(line);
	return (0);
}

void	do_heredoc_loop(t_shell *shell, t_hd_ctx *ctx)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (handle_hd_line(shell, ctx, line))
			break ;
	}
}
