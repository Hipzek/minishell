/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:22:16 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/15 19:35:46 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_strcpy(const char *src, char *dest)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (*dest);
}

char	*ft_strdup(const char *src)
{
	int		len;
	char	*dest;

	dest = NULL;
	len = ft_strlen(src);
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		return (NULL);
	ft_strcpy(src, dest);
	return (dest);
}
/*
#include <stdio.h>
int     main(void)
{
	char *src = "Helfeefefeflo iWoefwfewfewfefwrld";
	char *new;

	new = ft_strdup(src);
	printf("%s", new);
	return (0);
}*/
