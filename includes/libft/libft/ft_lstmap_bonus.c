/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:18:41 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/24 20:26:37 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_add_new(t_list **lst, void *content, void (*del)(void *))
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
	{
		del(content);
		ft_lstclear(lst, del);
		return (NULL);
	}
	ft_lstadd_back(lst, new);
	return (*lst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	res = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (!ft_add_new(&res, content, del))
			return (NULL);
		lst = lst->next;
	}
	return (res);
}

/*
#include <stdio.h>
void *dup_int(void *n)
{
	int	*new = malloc(sizeof(int));
	
	if(!new)
		return (NULL);
	*new = (*(int *)n) * 2;
	return (new);
}

void del_int(void *n)
{
	free(n);
}

int main(void)
{
	t_list	*lst = NULL;
	t_list	*mapped;
    	int	a = 1, b = 2, c = 3;

	ft_lstadd_back(&lst, ft_lstnew(&a));
	ft_lstadd_back(&lst, ft_lstnew(&b));
	ft_lstadd_back(&lst, ft_lstnew(&c));

	mapped = ft_lstmap(lst, dup_int, del_int);

	ft_lstclear(&mapped, del_int);
	return (0);
}*/
