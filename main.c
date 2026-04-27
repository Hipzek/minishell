/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:20:37 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/04/27 14:20:10 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	//t_shell	shell;
	char	*line;

	//init_shell(&shell, envp); // TODO
	// --> Malloc env + met exit_code = 0 + saved stdin/stdout
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		// LEXER (HISHEM) -> liste de token (shell.token)
		// PARSEUR/SYNTAX -> valid_syntax(shell.token)
		// CMD TABLE -> liste de cmd = cmd_table(shell.token)
		// EXPAND (HISHEM) -> $VAR, $?
		// EXEC -> exec_pipeline(shell)
		// 	----> fork() --> exec_chil()
		// 		     --> apply_redir()
		// 		     --> is_builtin() / exec_builtin()
		// 	 	     --> path() -> execve()
		// 	----> wait_pipeline()
	}
	// return (shell.exit_code);
	return (0);
}
