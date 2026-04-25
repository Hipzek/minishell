#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef enum    e_char_type
{
    CHAR_SEP = 0,
    CHAR_S_QUOTE = 1,
    CHAR_D_QUOTE = 2,
    CHAR_PIPE = 3,
    CHAR_REDIR = 4,
    CHAR_OTHER = 5
}   t_char_type;

typedef enum    e_action
{
    ACT_CONTINUE = 0,
    ACT_FLUSH = 1,
    ACT_EMIT_PIPE = 2,
    ACT_EMIT_REDIR = 3,
    ACT_ERROR = 4
}   t_action;

typedef enum    e_token_type
{
    TOK_WORD = 0,
    TOK_PIPE = 1,
    TOK_REDIR_IN = 2,
    TOK_REDIR_OUT = 3,
    TOK_APPEND = 4,
    TOK_HERE_DOC = 5
}   t_token_type;

typedef enum    e_state
{
    NORMAL = 0,
    IN_SQUOTE = 1,
    IN_DQUOTE = 2   
}   t_state;


typedef struct s_lst
{
    char            *value;
    t_token_type    token_type;
    struct s_lst     *next;
} t_lst;


typedef struct   s_struct_lex
{
    char             *raw;
    int              i;
    int              start;
    t_state          state;
    t_lst            *head_lst;
}   t_struct_lex;

// FONCTION LIBFT
char       
*ft_substr(const char *s, unsigned int start, size_t len);


// FONCTION T_LIST
t_lst 
*ft_new_node(char *value_str, t_token_type type);
int 
ft_add_back(t_lst **head_lst, t_lst *new);
t_lst   
*ft_found_last_lst(t_lst *head_lst);
int 
ft_print_link_c(t_lst *head_lst);


// FONCTION EXECUTEUR DU LEXEUR
int 
ft_do_lex(t_struct_lex *lex);
int     
ft_exec_action(t_struct_lex *lex, t_action action);
void    
ft_init_stuct_lex(t_struct_lex *lex);
t_char_type 
ft_get_char_type(char c);
void
ft_fill_state_table(t_state state_tab[3][6]);
void
ft_fill_action_table(t_action action_tab[3][6]);


// FONCTION ACT
int
ft_act_continue(t_struct_lex *lex);
int
ft_act_flush(t_struct_lex *lex);
int
ft_act_emit_redir(t_struct_lex *lex);
int
ft_act_emit_pipe(t_struct_lex *lex);


// FONCTION SOUS ACT
int     
ft_flush(t_struct_lex *lex);
int
ft_append(t_struct_lex *lex);
int
ft_heredoc(t_struct_lex *lex);
int
ft_redir_out(t_struct_lex *lex);
int
ft_redir_in(t_struct_lex *lex);

# endif