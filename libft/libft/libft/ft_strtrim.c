/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:43:25 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/13 13:56:41 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trim;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && is_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_set(s1[end - 1], set))
		end--;
	trim = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!trim)
		return (NULL);
	ft_strlcpy(trim, s1 + start, end - start + 1);
	return (trim);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*str1 = " Hello World! ";
	char	*str2 = "___42___";
	char	*trim1 = ft_strtrim(str1, " ");
	char	*trim2 = ft_strtrim(str2, "_");

	printf("'%s'\n", trim1); // 'Hello World!'
	printf("'%s'\n", trim2); // '42'

	free(trim1);
	free(trim2);
	return (0);
}*/
