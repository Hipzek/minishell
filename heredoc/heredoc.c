/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:47:10 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/10 13:01:04 by hbelleuv         ###   ########.fr       */
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
Expand les $VAR d'env
guillemets ignoriees
*/
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
		if (str[i] == '$' && is_valid_dollar(str[i + 1]))
			res = append_var_value(shell, res, str, &i);
		else
		{
			res = ft_strjoin_char(res, str[i]);
			i++;
		}
	}
	free(str);
	return (res);
}

static void	do_heredoc_loop(t_shell *shell, char *real_delim,
int expand_flag, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			printf("minishell: warning: ");
			printf("here-document delimited by end-of-file (wanted `%s')\n", real_delim);
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

static void	heredoc_child(t_shell *shell, char *real_delim,
int expand_flag, int fd[2])
{
	close(fd[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	do_heredoc_loop(shell, real_delim, expand_flag, fd[1]);
	free(real_delim);
	close(fd[1]);
	exit(0);
}

static int	heredoc_parent(t_shell *shell, char *real_delim,
int fd[2], pid_t pid)
{
	int	status;

	close(fd[1]);
	free(real_delim);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_inter_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(fd[0]);
		shell->exit_code = 130;
		write(1, "\n", 1);
		return (-1);
	}
	return (fd[0]);
}

// Lit l'entree utilisateur jusqu'au EOF et renvoie le fd de lecture (fd)
int	read_heredoc(t_shell *shell, char *delim_token)
{
	int		fd[2];
	pid_t	pid;
	char	*real_delim;
	int		expand_flag;

	expand_flag = !has_quotes(delim_token);
	real_delim = clean_token_value(delim_token);
	if (pipe(fd) == -1)
		return (free(real_delim), -1);
	pid = fork();
	if (pid == -1)
		return (close(fd[0]), close(fd[1]), free(real_delim), -1);
	if (pid == 0)
		heredoc_child(shell, real_delim, expand_flag, fd);
	return (heredoc_parent(shell, real_delim, fd, pid));
}
