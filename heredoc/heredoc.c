/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:47:10 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/15 15:30:05 by hbelleuv         ###   ########.fr       */
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
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				res = append_var_value(shell, res, str, &i, NORMAL);
			else if (ft_isdigit(str[i + 1]))
				i += 2;
			else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
				res = append_var_value(shell, res, str, &i, NORMAL);
			else
			{
				res = ft_strjoin_char(res, str[i]);
				i++;
			}
		}
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
		if (g_sig == SIGINT)
		{
			free(line);
			break ;
		}
		if (line == NULL)
		{
			printf("minishell: warning: here-document");
			printf(" delimited by end-of-file (wanted `%s')\n", real_delim);
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
int expand_flag, int fd[2], t_cmd *current_cmd)
{
	close(fd[0]);
	g_sig = 0;
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	do_heredoc_loop(shell, real_delim, expand_flag, fd[1]);
	free(real_delim);
	free_shell(shell);
	free_cmd_lst(current_cmd);
	close(fd[1]);
	if (g_sig == SIGINT)
		exit(130);
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
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		close(fd[0]);
		shell->exit_code = 130;
		return (-1);
	}
	return (fd[0]);
}

// Lit l'entree utilisateur jusqu'au EOF et renvoie le fd de lecture (fd)
int	read_heredoc(t_shell *shell, char *delim_token, t_cmd *current_cmd)
{
	int		fd[2];
	pid_t	pid;
	char	*real_delim;
	int		expand_flag;

	expand_flag = !has_quotes(delim_token);
	printf("flag de l'expand heredoc = %i \n", expand_flag);
	real_delim = clean_token_value(delim_token);
	if (pipe(fd) == -1)
		return (free(real_delim), close(shell->saved_stdin), close(shell->saved_stdout), -1);
	pid = fork();
	if (pid == -1)
		return (close(shell->saved_stdin), close(shell->saved_stdout), close(fd[0]), close(fd[1]), free(real_delim), -1);
	if (pid == 0)
		heredoc_child(shell, real_delim, expand_flag, fd, current_cmd);
	return (heredoc_parent(shell, real_delim, fd, pid));
}
