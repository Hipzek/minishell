/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:47:10 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 20:06:29 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
HEREDOC :

1. TOUS les Heredocs s'exécutent AVANT la moindre exécution de commande :
exemple : si cat << A | grep "bonjour" << B
Ne pas lancer de fork tout de suite
d'abord afficher > pour le document A puis le doc B
Et SEULEMENT ensuite lancer l'exec du pipeline

2. Le token qui suit le << est le dilimiteur (EOF)
Vis a vis des guillemets :
- SI le delimiteur n'a pas de guillemets :
  - il faut expand les $VAR a l'interieur du texte tape par l'utilisateur
- SI le dilimiteur a des guillemets simple ou double :
  - aucune expansion a faire

3. Signaux (Comportement specifique durant le heredoc)
- Ctrl + C : interrompt instantanement la lecture et la commande est annulee 
($? = 130)
- Ctrl + D : Pas un cas erreur ( == NULL , "EOF forcee")
	     et garde le donc deja tapee
*/

#include "../includes/minishell.h"

static void	warn_eof(char *delim)
{
	ft_putstr_fd("minishell: warning: here-document delimited", STDERR_FILENO);
	ft_putstr_fd("by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delim, STDERR_FILENO);
	ft_putstr_fd("`)", STDERR_FILENO);
}

static void	hd_expand_init(t_expand *exp, t_shell *shell, char *str)
{
	exp->shell = shell;
	exp->res = ft_strdup("");
	exp->state = NORMAL;
	exp->str = str;
	exp->i = 0;
}

/*
Expand les $VAR d'env
guillemets ignoriees
*/
static char	*hd_process_dollar(t_shell *shell, char *res, char *str, int *i)
{
	t_expand	exp;
//	char		*tmp;

//	tmp = res;
	hd_expand_init(&exp, shell, str);
	exp.res = res;
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
		return (res);
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

static int	hd_should_stop(char *line, char *real_delim, t_heredoc *hd)
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
	(void)hd;
	return (0);
}

void	do_heredoc_loop(t_heredoc *hd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (hd_should_stop(line, hd->real_delim, hd))
			break ;
		if (hd->expand_flag)
			line = expand_heredoc_line(hd->shell, line);
		ft_putendl_fd(line, hd->write_fd);
		free(line);
	}
}
