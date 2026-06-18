/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:47:10 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	heredoc_child(t_shell *shell, t_hd_ctx *ctx, t_cmd *current_cmd)
{
	struct sigaction	sa;

	close(ctx->fd[0]);
	g_sig = 0;
	sa.sa_handler = heredoc_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	do_heredoc_loop(shell, ctx);
	free(ctx->delim);
	free_shell(shell);
	free_cmd_lst(current_cmd);
	close(ctx->fd[1]);
	if (g_sig == SIGINT)
		exit(130);
	exit(0);
}

static int	heredoc_parent(t_shell *shell, t_hd_ctx *ctx, pid_t pid)
{
	int					status;
	struct sigaction	old_sa;

	close(ctx->fd[1]);
	free(ctx->delim);
	disable_sigint(&old_sa);
	waitpid(pid, &status, 0);
	restore_sigint(&old_sa);
	setup_inter_signals();
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		close(ctx->fd[0]);
		shell->exit_code = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		return (-1);
	}
	return (ctx->fd[0]);
}

int	read_heredoc(t_shell *shell, char *delim_token, t_cmd *current_cmd)
{
	t_hd_ctx	ctx;
	pid_t		pid;

	ctx.expand = !has_quotes(delim_token);
	ctx.delim = clean_token_value(delim_token);
	if (pipe(ctx.fd) == -1)
		return (free(ctx.delim), close(shell->saved_stdin),
			close(shell->saved_stdout), -1);
	pid = fork();
	if (pid == -1)
		return (close(shell->saved_stdin), close(shell->saved_stdout),
			close(ctx.fd[0]), close(ctx.fd[1]), free(ctx.delim), -1);
	if (pid == 0)
		heredoc_child(shell, &ctx, current_cmd);
	return (heredoc_parent(shell, &ctx, pid));
}
