/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:20:37 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	init_struct_lex(t_struct_lex *lex)
{
	lex->raw = NULL;
	lex->i = 0;
	lex->start = -1;
	lex->state = NORMAL;
	lex->head_lst = NULL;
}

static void	exec_tokens(t_shell *shell)
{
	if (valid_syntax(shell->token) == 0)
	{
		expand_tokens(shell);
		remove_quotes(shell);
		shell->cmd = cmd_table(shell);
		if (shell->cmd)
		{
			setup_exec_signals();
			shell->exit_code = exec_pipeline(shell);
		}
	}
	else
		shell->exit_code = 2;
	free_token_lst(shell->token);
	shell->token = NULL;
	if (shell->cmd)
	{
		free_cmd_lst(shell->cmd);
		shell->cmd = NULL;
	}
}

static void	process_line(t_shell *shell, char *line)
{
	t_struct_lex	lex;

	init_struct_lex(&lex);
	lex.raw = line;
	if (ft_do_lex(&lex) == 0 && lex.head_lst != NULL)
	{
		shell->token = lex.head_lst;
		exec_tokens(shell);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	*line;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
	while (1)
	{
		setup_inter_signals();
		if (g_sig == SIGINT)
			shell.exit_code = 130;
		g_sig = 0;
		line = readline("minishell> ");
		if (!line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			clean_and_exit(&shell, shell.exit_code);
		}
		if (*line)
			add_history(line);
		process_line(&shell, line);
		free(line);
	}
	return (0);
}
