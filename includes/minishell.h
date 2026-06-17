/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:27:45 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 02:57:58 by hbelleuv         ###   ########.fr       */
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
# include <limits.h>
# include "libft/libft.h"
# include <sys/stat.h>

extern volatile sig_atomic_t	g_sig;
typedef struct s_redir			t_redir;
typedef struct s_token			t_token;
typedef struct sigaction		t_sa;

typedef enum e_char_type
{
	CHAR_SEP = 0,
	CHAR_S_QUOTE = 1,
	CHAR_D_QUOTE = 2,
	CHAR_PIPE = 3,
	CHAR_REDIR = 4,
	CHAR_OTHER = 5
}	t_char_type;

typedef enum e_action
{
	ACT_CONTINUE = 0,
	ACT_FLUSH = 1,
	ACT_EMIT_PIPE = 2,
	ACT_EMIT_REDIR = 3,
	ACT_ERROR = 4
}	t_action;

typedef enum e_token_type
{
	WORD = 0,
	PIPE = 1,
	REDIR_IN = 2,
	REDIR_OUT = 3,
	APPEND = 4,
	HEREDOC = 5,
}	t_token_type;

typedef enum e_state
{
	NORMAL = 0,
	IN_SQUOTE = 1,
	IN_DQUOTE = 2,
}	t_state;

typedef struct s_struct_lex
{
	char		*raw;
	int			i;
	int			start;
	t_state		state;
	t_token		*head_lst;
}	t_struct_lex;

typedef struct s_token
{
	t_token_type	token_type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				heredoc_fd;
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
	t_token	*token;
	t_cmd	*cmd;
	int		saved_stdin;
	int		saved_stdout;
	int		exit_code;
}	t_shell;

// --------- FONCTIONS -------------

// FONCTION LIBFT
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);

// EXPAND
void		expand_tokens(t_shell *shell);
int			is_valid_dollar(char c);
char		*append_var_value(t_shell *shell, char *res,
				char *str, int *i, t_state state);

// REMOVE QUOTES
char		*clean_token_value(char *str);
void		remove_quotes(t_shell *shell);

// HEREDOC
int			has_quotes(char *str);
int			read_heredoc(t_shell *shell, char *delim_token, t_cmd *current_cmd);
void		do_heredoc_loop(t_shell *shell, char *real_delim,
	int expand_flag, int write_fd);

// TABLE CMD
t_cmd		*cmd_table(t_shell *shell);
t_cmd		*parse_cmd(t_shell *shell, t_token **token);
int		count_args(t_token *token);
int		fill_cmd_args(t_shell *shell, t_cmd *cmd, t_token **token);

// EXEC
int			exec_pipeline(t_shell *shell);
void		exec_child(t_shell *shell, t_cmd *cmd,
				int relay_fd, int pipe_fd[2]);
void		apply_redir(t_shell *shell, t_cmd *cmd);
int			apply_redir_parent(t_shell *shell, t_cmd *cmd);
char		*path(char *cmd, char **envp);
int			is_builtin(t_cmd *cmd);
int			exec_builtin(t_shell *shell, t_cmd *cmd);
void		wait_pipeline(t_shell *shell, pid_t last_pid);

// BUILT IN
int			ft_echo(t_shell *shell, t_cmd *cmd);
int			ft_pwd(t_shell *shell, t_cmd *cmd);
int			ft_cd(t_shell *shell, t_cmd *cmd);
int			ft_env(t_shell *shell, t_cmd *cmd);
int			ft_export(t_shell *shell, t_cmd *cmd);
int			ft_unset(t_shell *shell, t_cmd *cmd);
int			ft_exit(t_shell *shell, t_cmd *cmd);
char		*get_env(t_shell *shell, char *name);
int			update_env(t_shell *shell, char *name, char *value);
int			is_valid_identifier(char *str);
void		print_export_line(char *env_str);
void		sort_env_ptrs(char **tab, int count);
int		print_sorted_env(t_shell *shell);

// GB
void		free_double_tab(char **tab);
void		free_cmd_lst(t_cmd *cmd);
void		free_token_lst(t_token *token);
void		free_shell(t_shell *shell);
void		clean_and_exit(t_shell *shell, int exit_code);

// SIGNALS
void		setup_inter_signals(void);
void		setup_exec_signals(void);
void		setup_child_signal(void);
void		handle_signal(int sig);
void		heredoc_sigint(int sig);
void		disable_sigint(struct sigaction *old_sa);
void		restore_sigint(struct sigaction *old_sa);

// ----------- LEXER + VALID_SYNTAX -------------

// VALID SYNTAX
int			valid_syntax(t_token *token);
int			is_redirection(t_token_type type);

// FONCTION T_LIST
t_token		*ft_new_node(char *value_str, t_token_type type);
int			ft_add_back(t_token **head_lst, t_token *new);
t_token		*ft_found_last_lst(t_token *head_lst);
int			ft_print_link_c(t_token *head_lst);

// FONCTION EXECUTEUR DU LEXEUR
int			ft_do_lex(t_struct_lex *lex);
int			ft_exec_action(t_struct_lex *lex, t_action action);
void		ft_init_stuct_lex(t_struct_lex *lex);
void		ft_fill_state_table(t_state state_tab[3][6]);
void		ft_fill_action_table(t_action action_tab[3][6]);
t_char_type	ft_get_char_type(char c);

// FONCTION ACT
int			ft_act_continue(t_struct_lex *lex);
int			ft_act_flush(t_struct_lex *lex);
int			ft_act_emit_redir(t_struct_lex *lex);
int			ft_act_emit_pipe(t_struct_lex *lex);

// FONCTION SOUS ACT
int			ft_flush(t_struct_lex *lex);
int			ft_append(t_struct_lex *lex);
int			ft_heredoc(t_struct_lex *lex);
int			ft_redir_out(t_struct_lex *lex);
int			ft_redir_in(t_struct_lex *lex);

// OUTPUT TESTS
void		ft_print_arr(char **arr);
void		ft_print_ttype(t_token_type type);
void		ft_print_token(t_token *token);
void		ft_print_redir(t_redir *redir);
void		ft_print_cmd(t_cmd *cmd);
void		ft_print_shell(t_shell *shell, int mod);

#endif
