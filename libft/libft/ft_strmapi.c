/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:49:24 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/14 12:49:40 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>
char	my_func(int i, char c)
{
	if (i % 2 == 0)
		return (c - 32); // met en MAJUSCULE si index pair
	return (c);
}

int	main(void)
{
	char	*s = "hello world";
	char	*result;

	result = ft_strmapi(s, my_func);
	printf("Avant : %s\n", s);
	printf("Après : %s\n", result);

	free(result);
	return (0);
}*/
