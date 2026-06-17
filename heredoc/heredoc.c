/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:47:10 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 21:55:00 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	warn_eof(char *delim)
{
	ft_putstr_fd("minishell: warning: here-document delimited", STDERR_FILENO);
	ft_putstr_fd("by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delim, STDERR_FILENO);
	ft_putstr_fd("`)\n", STDERR_FILENO);
}

static char	*hd_expand_init(t_expand *exp, t_shell *shell, char *str, char *res)
{
	exp->shell = shell;
	exp->res = res;
	exp->state = NORMAL;
	exp->str = str;
	exp->i = 0;
	return (res);
}

static char	*hd_process_dollar(t_shell *shell, char *res, char *str, int *i)
{
	t_expand	exp;

	exp.res = hd_expand_init(&exp, shell, str, res);
	exp.i = *i;
	ft_append_dollar_expansion(&exp);
	*i = exp.i;
	return (exp.res);
}

static char	*expand_heredoc_line(t_shell *shell, char *str)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	if (!str || !res)
		return (free(str), res);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			res = hd_process_dollar(shell, res, str, &i);
		else
		{
			res = ft_strjoin_char(res, str[i]);
			i++;
		}
	}
	free(str);
	return (res);
}

static int	hd_should_stop(char *line, char *real_delim)
{
	if (g_sig == SIGINT || line == NULL)
	{
		if (line == NULL && g_sig != SIGINT)
			warn_eof(real_delim);
		free(line);
		return (1);
	}
	if (ft_strcmp(line, real_delim) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

void	do_heredoc_loop(t_heredoc *hd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (hd_should_stop(line, hd->real_delim))
			break ;
		if (hd->expand_flag)
			line = expand_heredoc_line(hd->shell, line);
		ft_putendl_fd(line, hd->write_fd);
		free(line);
	}
}
