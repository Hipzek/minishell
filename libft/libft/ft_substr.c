/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:09:55 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/17 12:11:16 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		sub = malloc(1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (len > s_len - start)
		len = s_len - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*str = "Hello World!";
	char	*sub1 = ft_substr(str, 0, 5);     // "Hello"
	char	*sub2 = ft_substr(str, 6, 5);     // "World"
	char	*sub3 = ft_substr(str, 20, 5);    // ""

	printf("sub1 = %s\n", sub1);
	printf("sub2 = %s\n", sub2);
	printf("sub3 = %s\n", sub3);

	free(sub1);
	free(sub2);
	free(sub3);

	return (0);
}
*/
