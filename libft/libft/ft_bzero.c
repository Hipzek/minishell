/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:00:30 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/12 14:58:00 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
/*
#include <stdio.h>
int	main(void)
{
	char	data[6] = "Hello";

	printf("Avant bzero : %s\n", data);
	ft_bzero(data, 5);
	printf("Après bzero : ");
	for (int i = 0; i < 6; i++)
		printf("%d ", data[i]);
	printf("\n");

	return (0);
}
*/
