/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:16:44 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/24 22:51:44 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/*
#include <stdio.h>
void    print_list(t_list *lst)
{
    while(lst != NULL)
    {
        printf("%s\n", (char *)lst->content);
        lst = lst->next;
    }
}

int main(void)
{
    t_list  *list = NULL;

    t_list  *node_1 = ft_lstnew(strdup("node_1"));
    t_list  *node_2 = ft_lstnew(strdup("node_2"));
    t_list  *node_3 = ft_lstnew(strdup("node_3"));
    ft_lstadd_front(&list, node_3);
    ft_lstadd_front(&list, node_2);
    ft_lstadd_front(&list, node_1);
    print_list(list);
}*/
