/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:01:11 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/24 22:52:30 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/*
#include <stdio.h>
int	main(void)
{
	char	src[10] = "Bonjour";
	char	dest[10];

	ft_memcpy(dest, src, 8); // copie le '\0' inclus
	printf("dest = \"%s\"\n", dest);

	int	arr1[3] = {1, 2, 3};
	int	arr2[3];

	ft_memcpy(arr2, arr1, sizeof(arr1));

	printf("arr2 = { %d, %d, %d }\n", arr2[0], arr2[1], arr2[2]);

	return (0);
}*/
