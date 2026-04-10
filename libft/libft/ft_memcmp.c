/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:12:35 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/24 22:52:17 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	i = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	char a[] = "Bonjour";
	char b[] = "Bonsoir";
	char c[] = "Bonjour";

	printf("a vs b (3 octets): %d\n", ft_memcmp(a, b, 3));
	printf("a vs b (7 octets): %d\n", ft_memcmp(a, b, 7));
	printf("a vs c (7 octets): %d\n", ft_memcmp(a, c, 7));

	return (0);
}*/
