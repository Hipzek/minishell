/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:26:58 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/24 22:54:47 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total_size;
	void			*ptr;

	total_size = nmemb * size;
	if (nmemb != 0 && total_size / nmemb != size)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}

/*
#include <stdio.h>
int	main(void)
{
	int	*tab;
	size_t	i;

	tab = ft_calloc(5, sizeof(int));
	if (!tab)
		return (1);

	for (i = 0; i < 5; i++)
		printf("tab[%zu] = %d\n", i, tab[i]); // Tous à 0 !

	free(tab);
	return (0);
}*/
