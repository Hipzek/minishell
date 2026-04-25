#include "minishell.h"


t_lst *
ft_new_node(char *value_str, t_token_type type){
    t_lst *new;

    if (!value_str)
        return (NULL);
    new = malloc(sizeof(t_lst));
    if (!new)
        return (NULL);
    new->value = value_str;
    new->token_type = type;
    new->next = NULL;
    return (new);
}

int 
ft_add_back(t_lst **head_lst, t_lst *new){

    t_lst      *current;

    if (!head_lst || !new)
        return (1);
    if ((*head_lst) == NULL)
        return((*head_lst) = new, 0);
    if (!(current = ft_found_last_lst(*head_lst)))
        return (1);
    current->next = new;
    return (0);
}

int 
ft_count_node_in_lst(t_lst *head_lst){

    t_lst  *current;
    int     count;

    if (!head_lst)
        return (-1);
    current = head_lst;
    count = 0;
    while (current != NULL){
        count++;
        current = current->next;
    }
    return (count);
}

t_lst * 
ft_found_last_lst(t_lst *head_lst){

    t_lst  *current;
    
    if (!head_lst)
        return (NULL);
    current = head_lst;
    while (current->next != NULL)
        current = current->next;
    return (current);
}
 
static char	*ft_token_type_name(t_token_type type)
{
	if (type == TOK_WORD)
		return ("WORD");
	if (type == TOK_PIPE)
		return ("PIPE");
	if (type == TOK_REDIR_IN)
		return ("REDIR_IN");
	if (type == TOK_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == TOK_APPEND)
		return ("APPEND");
	if (type == TOK_HERE_DOC)
		return ("HERE_DOC");
	return ("UNKNOWN");
}

int 
ft_print_link_c(t_lst *head_lst){

    t_lst  *current;
    
    if (!head_lst)
        return (1);
    current = head_lst;
    while (current != NULL){
        printf("[\"%s\" | %s] ->",current->value, ft_token_type_name(current->token_type));
        current = current->next;
    }
        printf("NULL\n");
    return (0);
}
