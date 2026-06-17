/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:47:10 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 02:28:27 by hbelleuv         ###   ########.fr       */
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

/*
#include <fcntl.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	debug_fds(const char *label)
{
	int	i;
	int	flags;

	ft_printf("[%s] PID=%d open fds: ", label, getpid());
	i = 0;
	while (i < 20)
	{
		flags = fcntl(i, F_GETFD);
		if (flags != -1)
			ft_printf("%d ", i);
		i++;
	}
	ft_printf("\n");
}
*/

static void	warn_eof(char *delim)
{
	ft_putstr_fd("minishell: warning: here-document delimited", STDERR_FILENO);
	ft_putstr_fd("by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delim, STDERR_FILENO);
	ft_putstr_fd("`)", STDERR_FILENO);
}

/*
Expand les $VAR d'env
guillemets ignoriees
*/
static char	*ft_process_dollar(t_shell *shell, char *res, char *str, int *i)
{
	if (str[*i + 1] == '?')
		res = append_var_value(shell, res, str, i, NORMAL);
	else if (ft_isdigit(str[*i + 1]))
		*i += 2;
	else if (ft_isalpha(str[*i + 1]) || str[*i + 1] == '_')
		res = append_var_value(shell, res, str, i, NORMAL);
	else
	{
		res = ft_strjoin_char(res, str[*i]);
		(*i)++;
	}
	return (res);
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
			res = ft_process_dollar(shell, res, str, &i);
		else
		{
			res = ft_strjoin_char(res, str[i]);
			i++;
		}
	}
	free(str);
	return (res);
}

void	do_heredoc_loop(t_shell *shell, char *real_delim,
	int expand_flag, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_sig == SIGINT || line == NULL)
		{
			if (line == NULL && g_sig != SIGINT)
				warn_eof(real_delim);
			free(line);
			break ;
		}
		if (ft_strcmp(line, real_delim) == 0)
		{
			free(line);
			break ;
		}
		if (expand_flag)
			line = expand_heredoc_line(shell, line);
		ft_putendl_fd(line, write_fd);
		free(line);
	}
}
