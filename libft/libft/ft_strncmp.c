/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:10:42 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/17 16:24:19 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("Test 1 : %d\n", ft_strncmp("Hello", "Hello", 5));
	printf("Test 2 : %d\n", ft_strncmp("Hello", "Hella", 5));
	printf("Test 3 : %d\n", ft_strncmp("Hello", "Hell", 5));
	printf("Test 4 : %d\n", ft_strncmp("Hell", "Hello", 5));
	printf("Test 5 : %d\n", ft_strncmp("Hello", "Hella", 3));
	return (0);
}*/
