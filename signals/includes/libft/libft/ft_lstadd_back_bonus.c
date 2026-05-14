/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:16:21 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/17 11:59:37 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

/*
#include <stdio.h>
int main(void)
{
    int a = 1, b = 2, c = 3;

    t_list *lst = ft_lstnew(&a);
    t_list *n2 = ft_lstnew(&b);
    t_list *n3 = ft_lstnew(&c);

    ft_lstadd_back(&lst, n2);
    ft_lstadd_back(&lst, n3);

    t_list *cur = lst;
    while (cur)
    {
        printf("%d\n", *(int *)cur->content);
        cur = cur->next;
    }

    // free
    free(n3);
    free(n2);
    free(lst);

    return 0;
}*/
