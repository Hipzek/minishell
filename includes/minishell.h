/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:27:45 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/05 15:10:09 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <stddef.h>
# include "libft/libft.h"

typedef struct s_redir	t_redir;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
	char			*path;
	pid_t			pid;
}	t_cmd;

typedef struct s_shell
{
	char	**env;
	int		exit_code;
	t_token	*token;
	t_cmd	*cmds;
	int		saved_stdin;
	int		saved_stdout;
}	t_shell;

// --------- FONCTIONS -------------

// TABLE CMD
t_cmd	*cmd_table(t_token *tokens);

// EXEC
int		exec_pipeline(t_cmd *cmd, char **envp);
void	exec_child(t_cmd *cmd, int relay_fd, int pipe_fd[2], char **envp);
void	apply_redir(t_cmd *cmd);
char	*path(char *cmd, char **envp);
int		is_builtin(t_cmd *cmd);
int		exec_builtin(t_cmd *cmd, char **envp);

// BUILTIN
int	update_env(t_shell *shell, char *name, char *value);

#endif
