/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:18:19 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/17 11:56:12 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
#include <stdio.h>
int main(void)
{
    int a = 1, b = 2, c = 3;

    t_list *n1 = ft_lstnew(&a);
    t_list *n2 = ft_lstnew(&b);
    t_list *n3 = ft_lstnew(&c);

    ft_lstadd_back(&n1, n2);
    ft_lstadd_back(&n1, n3);

    t_list *last = ft_lstlast(n1);

    printf("Last value = %d\n", *(int *)last->content);

    free(n3);
    free(n2);
    free(n1);

    return 0;
}
*/
