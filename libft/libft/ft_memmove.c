/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:01:48 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/24 22:53:41 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d < s)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
		while (n--)
			d[n] = s[n];
	return (dest);
}
/*
#include <stdio.h>
int main(void)
{
	char str[20] = "Hello World";
	char overlap[20] = "123456789";

	// Cas 1 : zones NON chevauchées
	ft_memmove(str + 6, str, 5);
	str[11] = '\0';
	printf("%s\n", str); // Output: Hello Hello

	// Cas 2 : zones chevauchées
	ft_memmove(overlap + 2, overlap, 5);
	printf("%s\n", overlap); // Output: 121234589

	return 0;
}
*/
