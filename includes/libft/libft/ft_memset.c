/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:09:00 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/23 18:25:59 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)dest;
	i = 0;
	while (i < count)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char	buffer[10];
	size_t	i;

	ft_memset(buffer, 'X', 9);
	buffer[9] = '\0'; // pour l'afficher comme une chaîne

	printf("buffer = \"%s\"\n", buffer);

	ft_memset(buffer, 0, 10); // tout mettre à zéro

	printf("après memset à 0 :\n");
	for (i = 0; i < 10; i++)
		printf("%d ", buffer[i]);
	printf("\n");

	return (0);
}
*/
