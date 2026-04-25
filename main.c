#include "minishell.h"

void    
ft_init_stuct_lex(t_struct_lex *lex)
{
    if (!lex)
        return;
    lex->raw = NULL;
    lex->i = 0;
    lex->start = -1;
    lex->state = NORMAL;
    lex->head_lst = NULL;
}

int 
main()
{
    t_struct_lex   lex;
    char            *raw;
    
    raw = readline("MS-THE-ONE$ ");
    if (!raw)
        return (1);
    ft_init_stuct_lex(&lex);
    lex.raw = raw;
    ft_do_lex(&lex);
    ft_print_link_c(lex.head_lst);
    return (0);
}

