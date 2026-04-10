/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:34:29 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/24 23:03:03 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len_src;
	size_t	len_dest;

	len_src = ft_strlen(src);
	len_dest = ft_strlen(dest);
	if (len_dest >= size)
		return (size + len_src);
	i = 0;
	while (src[i] && (len_dest + i) < (size - 1))
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	if (len_dest < size)
		dest[len_dest + i] = '\0';
	return (len_dest + len_src);
}
/*
#include <stdio.h>
int main(void)
{
	char buffer[15] = "Hello";
	size_t ret;

	ret = strlcat(buffer, " world!", sizeof(buffer));
	printf("buffer = \"%s\"\n", buffer);
	printf("ret = %zu\n", ret);
	return (0);
}*/
