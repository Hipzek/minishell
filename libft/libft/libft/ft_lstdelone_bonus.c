/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:17:36 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/17 11:20:06 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/*
#include <stdio.h>
void free_int(void *p)
{
    free(p);
}

int main(void)
{
    int *n = malloc(sizeof(int));
    *n = 42;

    t_list *node = ft_lstnew(n);

    ft_lstdelone(node, free_int);

    printf("OK - node deleted\n");

    return 0;
}*/
