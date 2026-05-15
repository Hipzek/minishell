/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:20:37 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/15 22:47:00 by hbelleuv         ###   ########.fr       */
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
	lex->head_lst = NULL; // CF renommer head_token
}

static char	**copy_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env && env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	init_shell(t_shell *shell, char **env)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->env = copy_env(env);
	shell->exit_code = 0;
	shell->saved_stdin = dup(STDIN_FILENO);
	shell->saved_stdout = dup(STDOUT_FILENO);
}

// LEXER (HISHEM) -> liste de token (shell.token)
		// PARSEUR/SYNTAX -> valid_syntax(shell.token)
		
		// HEREDOC + EXPAND + REMOVE QUOTES
	
		// CMD TABLE -> liste de cmd = cmd_table(shell.token)

		// EXEC -> exec_pipeline(shell)
		// 	----> fork() --> exec_chil()
		// 		     --> apply_redir()
		// 		     --> is_builtin() / exec_builtin()
		// 	 	     --> path() -> execve()
		// 	----> wait_pipeline()


int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	*line;
	t_struct_lex	lex;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
	while (1)
	{
		setup_inter_signals();
		if (g_sig == SIGINT)
		{
			shell.exit_code = 130;
			g_sig = 0;
		}
		line = readline("minishell> ");
		if (!line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			clean_and_exit(&shell, shell.exit_code);
		}
		if (*line)
			add_history(line);
		
		init_struct_lex(&lex);
		lex.raw = line;
		if (ft_do_lex(&lex) == 0 && lex.head_lst != NULL)
		{
			shell.token = lex.head_lst;
			if (shell.token && valid_syntax(shell.token) == 0)
			{
				expand_tokens(&shell);
				// rm quotes : remove_quotes(&shell);
				shell.cmd = cmd_table(shell.token);
				if (shell.cmd)
				{
					setup_exec_signals();
					shell.exit_code = exec_pipeline(&shell);
				}
			}
			else
				shell.exit_code = 2;
			free_token_lst(shell.token);
			shell.token = NULL;
		}
		if (shell.cmd)
		{
			free_cmd_lst(shell.cmd);
			shell.cmd = NULL;
		}
		free(line);
	}
	return (0);
}
