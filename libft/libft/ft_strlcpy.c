/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:19:33 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/14 16:29:15 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (src[i])
		i++;
	len = i;
	if (size == 0)
		return (len);
	i = 0;
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}
/*
#include <stdio.h>
int	main(void)
{
	char	dst1[10];
	char	dst2[5];
	char	dst3[1];
	size_t	ret;

	ret = ft_strlcpy(dst1, "Hello", sizeof(dst1));
	printf("dst1=\"%s\" ret=%zu\n", dst1, ret);

	ret = ft_strlcpy(dst2, "Bonjour", sizeof(dst2));
	printf("dst2=\"%s\" ret=%zu\n", dst2, ret);

	ret = ft_strlcpy(dst3, "a", sizeof(dst3));
	printf("dst3=\"%s\" ret=%zu\n", dst3, ret);

	return (0);
}*/
