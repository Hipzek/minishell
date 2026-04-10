/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:18:01 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/17 11:18:10 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*
#include <stdio.h>
void print_int(void *p)
{
    printf("%d\n", *(int *)p);
}

int main(void)
{
    int a = 1, b = 2, c = 3;

    t_list *n1 = ft_lstnew(&a);
    t_list *n2 = ft_lstnew(&b);
    t_list *n3 = ft_lstnew(&c);

    ft_lstadd_back(&n1, n2);
    ft_lstadd_back(&n1, n3);

    ft_lstiter(n1, print_int);

    free(n3);
    free(n2);
    free(n1);

    return 0;
}*/
