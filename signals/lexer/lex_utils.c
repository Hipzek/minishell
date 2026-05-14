/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:08:56 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/14 17:13:02 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_char_type	ft_get_char_type(char c)
{
    if (c == ' ' || c == '\t')
        return (CHAR_SEP);
    if (c == '\'')
        return(CHAR_S_QUOTE);
    if (c == '\"')
        return (CHAR_D_QUOTE);
    if (c == '|')
        return (CHAR_PIPE);
    if (c == '<' || c == '>')
        return (CHAR_REDIR);
    else
        return(CHAR_OTHER);
}

void	ft_fill_state_table(t_state state_tab[3][6])
{
    if (!state_tab)
        return;
    state_tab[NORMAL][CHAR_SEP] = NORMAL;
    state_tab[NORMAL][CHAR_S_QUOTE] = IN_SQUOTE;
    state_tab[NORMAL][CHAR_D_QUOTE] = IN_DQUOTE;
    state_tab[NORMAL][CHAR_PIPE] = NORMAL;
    state_tab[NORMAL][CHAR_REDIR] = NORMAL;
    state_tab[NORMAL][CHAR_OTHER] = NORMAL;

    state_tab[IN_SQUOTE][CHAR_SEP] = IN_SQUOTE;
    state_tab[IN_SQUOTE][CHAR_S_QUOTE] = NORMAL;
    state_tab[IN_SQUOTE][CHAR_D_QUOTE] = IN_SQUOTE;
    state_tab[IN_SQUOTE][CHAR_PIPE] = IN_SQUOTE;
    state_tab[IN_SQUOTE][CHAR_REDIR] = IN_SQUOTE;
    state_tab[IN_SQUOTE][CHAR_OTHER] = IN_SQUOTE;

    state_tab[IN_DQUOTE][CHAR_SEP] = IN_DQUOTE;
    state_tab[IN_DQUOTE][CHAR_S_QUOTE] = IN_DQUOTE;
    state_tab[IN_DQUOTE][CHAR_D_QUOTE] = NORMAL;
    state_tab[IN_DQUOTE][CHAR_PIPE] = IN_DQUOTE;
    state_tab[IN_DQUOTE][CHAR_REDIR] = IN_DQUOTE;
    state_tab[IN_DQUOTE][CHAR_OTHER] = IN_DQUOTE;
}

void	ft_fill_action_table(t_action action_tab[3][6])
{
    if (!action_tab)
        return;
    action_tab[NORMAL][CHAR_SEP] = ACT_FLUSH;
    action_tab[NORMAL][CHAR_S_QUOTE] = ACT_CONTINUE;
    action_tab[NORMAL][CHAR_D_QUOTE] = ACT_CONTINUE;
    action_tab[NORMAL][CHAR_PIPE] = ACT_EMIT_PIPE;
    action_tab[NORMAL][CHAR_REDIR] = ACT_EMIT_REDIR;
    action_tab[NORMAL][CHAR_OTHER] = ACT_CONTINUE;

    action_tab[IN_SQUOTE][CHAR_SEP] = ACT_CONTINUE;
    action_tab[IN_SQUOTE][CHAR_S_QUOTE] = ACT_CONTINUE;
    action_tab[IN_SQUOTE][CHAR_D_QUOTE] = ACT_CONTINUE;
    action_tab[IN_SQUOTE][CHAR_PIPE] = ACT_CONTINUE;
    action_tab[IN_SQUOTE][CHAR_REDIR] = ACT_CONTINUE;
    action_tab[IN_SQUOTE][CHAR_OTHER] = ACT_CONTINUE ;

    action_tab[IN_DQUOTE][CHAR_SEP] = ACT_CONTINUE;
    action_tab[IN_DQUOTE][CHAR_S_QUOTE] = ACT_CONTINUE ;
    action_tab[IN_DQUOTE][CHAR_D_QUOTE] = ACT_CONTINUE;
    action_tab[IN_DQUOTE][CHAR_PIPE] = ACT_CONTINUE;
    action_tab[IN_DQUOTE][CHAR_REDIR] = ACT_CONTINUE;
    action_tab[IN_DQUOTE][CHAR_OTHER] = ACT_CONTINUE;
}

int	ft_exec_action(t_struct_lex *lex, t_action action)
{
    if (!lex || action == ACT_ERROR)
        return (1);
    if (action == ACT_CONTINUE)
        return (ft_act_continue(lex));
    if (action == ACT_FLUSH)
        return (ft_act_flush(lex));
    if (action == ACT_EMIT_PIPE)
        return (ft_act_emit_pipe(lex));
    if (action == ACT_EMIT_REDIR)
        return (ft_act_emit_redir(lex));
    return (1);
}


int	ft_act_continue(t_struct_lex *lex)
{
    if (!lex)
        return (1);
    if (lex->start == -1)
        lex->start = lex->i;
    lex->i += 1;
    return(0);    
}
int	ft_act_emit_pipe(t_struct_lex *lex)
{
    t_token   *new_node;

    if (!lex)
        return (1);
    if (ft_flush(lex))
        return(1);
    lex->start = -1;
    new_node = ft_new_node("|", PIPE);
    if (!new_node)
        return (1);
    if (ft_add_back(&lex->head_lst, new_node))
        return (1);
    lex->i += 1;
    return (0);
}

int	ft_act_flush(t_struct_lex *lex)
{
    if (!lex)
        return(1);
    if (ft_flush(lex))
        return(1);
    lex->start = -1;
    lex->i += 1;
    return (0);
}
int	ft_act_emit_redir(t_struct_lex *lex)
{
    char    redir;
    char    next;
    
    if (!lex)
        return (1);
    redir = lex->raw[lex->i];
    next = lex->raw[lex->i + 1];
    if (redir == '>' && next == '>')
        return (ft_append(lex));
    else if (redir == '<' && next == '<') 
        return (ft_heredoc(lex));
    else if (redir == '<')
        return (ft_redir_in(lex));
    else if (redir == '>')
        return (ft_redir_out(lex));
    return (1);
}

int	ft_flush(t_struct_lex *lex)
{
    char    *value;
    t_token   *new_node;

    if (!lex)
        return (1);
    if (lex->start == -1)
        return (0);
    value = ft_substr(lex->raw, lex->start, (lex->i - lex->start));
    if (!value)
        return (1);
    new_node = ft_new_node(value, WORD);
    free(value);
    if (!new_node)
    {
//	    free(new_node); // RAJOUE ICI
        return (1);
    }
    if (ft_add_back(&lex->head_lst, new_node))
    {
	    free_token_lst(new_node);
	    return (1);
    }
    return(0);
}

int	ft_append(t_struct_lex *lex)
{
    t_token   *new_node;

    if (!lex)
        return(1);
    if (ft_flush(lex))
        return(1);
    lex->start = -1; 
    new_node = ft_new_node(">>", APPEND);
    if (!new_node)
        return (1);
    if (ft_add_back(&lex->head_lst, new_node))
        return (1);
    lex->i += 2;

    return (0);
}
int	ft_heredoc(t_struct_lex *lex)
{
    t_token   *new_node;

    if (!lex)
        return(1);
    if (ft_flush(lex))
        return(1);
    lex->start = -1; 
    new_node = ft_new_node("<<", HEREDOC);
    if (!new_node)
        return (1);
    if (ft_add_back(&lex->head_lst, new_node))
        return (1);
    lex->i += 2;
    return (0);
}

int	ft_redir_out(t_struct_lex *lex)
{
    t_token   *new_node;

    if (!lex)
        return (1);
    if (ft_flush(lex))
        return (1);
    lex->start = -1; 
    new_node = ft_new_node(">", REDIR_OUT);
    if (!new_node)
        return (1);
    if (ft_add_back(&lex->head_lst, new_node))
        return (1);
    lex->i += 1;
    return (0);
}
int	ft_redir_in(t_struct_lex *lex)
{
    t_token   *new_node;

    if (!lex)
        return(1);
    if (ft_flush(lex))
        return(1);
    lex->start = -1; 
    new_node = ft_new_node("<", REDIR_IN);
    if (!new_node)
        return (1);
    if (ft_add_back(&lex->head_lst, new_node))
        return (1);
    lex->i += 1;
    return (0);
}
