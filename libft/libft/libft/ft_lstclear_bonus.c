/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:17:15 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/17 11:17:24 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

/*
#include <stdio.h>
void free_content(void *p)
{
    free(p);
}

int main(void)
{
    t_list *lst = NULL;

    for (int i = 0; i < 3; i++)
    {
        int *n = malloc(sizeof(int));
        *n = i;
        ft_lstadd_back(&lst, ft_lstnew(n));
    }

    ft_lstclear(&lst, free_content);

    if (lst == NULL)
        printf("List cleared successfully\n");
}*/
