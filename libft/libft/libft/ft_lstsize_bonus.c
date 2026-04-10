/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:19:16 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/17 11:55:52 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

/*
#include <stdio.h>
int main(void)
{
    int a = 10, b = 20, c = 30;

    t_list *l1 = ft_lstnew(&a);
    t_list *l2 = ft_lstnew(&b);
    t_list *l3 = ft_lstnew(&c);

    ft_lstadd_front(&l1, l2);
    ft_lstadd_front(&l1, l3);

    printf("List size = %d\n", ft_lstsize(l1)); // 3

    free(l1->next->next);
    free(l1->next);
    free(l1);
    return 0;
}*/
