/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 12:11:35 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/10 12:12:14 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Verifie si la chaine contient des guillemets simples ou doubles
Renvoie 1 si vrai et 0 si faux
*/
int	has_quotes(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static void	heredoc_child(t_shell *shell, char *real_delim,
int expand_flag, int fd[2], t_cmd *current_cmd)
{
	struct sigaction	sa;

	close(fd[0]);
	g_sig = 0;
	sa.sa_handler = heredoc_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
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
	int					status;
	struct sigaction	old_sa;

	close(fd[1]);
	free(real_delim);
	disable_sigint(&old_sa);
	waitpid(pid, &status, 0);
	restore_sigint(&old_sa);
	setup_inter_signals();
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		close(fd[0]);
		shell->exit_code = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
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
	real_delim = clean_token_value(delim_token);
	if (pipe(fd) == -1)
		return (free(real_delim), close(shell->saved_stdin),
			close(shell->saved_stdout), -1);
	pid = fork();
	if (pid == -1)
		return (close(shell->saved_stdin), close(shell->saved_stdout),
			close(fd[0]), close(fd[1]), free(real_delim), -1);
	if (pid == 0)
		heredoc_child(shell, real_delim, expand_flag, fd, current_cmd);
	return (heredoc_parent(shell, real_delim, fd, pid));
}
