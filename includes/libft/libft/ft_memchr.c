/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:51:47 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/24 22:57:56 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)&ptr[i]);
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
int	main(void)
{
	char	data[] = "abcdefg";

	char *res1 = ft_memchr(data, 'd', 7);
	char *res2 = ft_memchr(data, 'x', 7);

	if (res1)
		printf("Trouvé : %s\n", res1); // affiche "defg"
	else
		printf("Pas trouvé\n");

	if (res2)
		printf("Trouvé : %s\n", res2);
	else
		printf("Pas trouvé\n"); // affiche "Pas trouvé"

	return (0);
}*/
