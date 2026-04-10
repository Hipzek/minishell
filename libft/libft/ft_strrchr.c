/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:51:37 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/14 15:32:14 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if ((char) c == '\0')
		return ((char *)s + i);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}

/*
#include <stdio.h>
int	main(void)
{
	const char *str = "bonjour";

	char *result1 = ft_strrchr(str, 'o');
	char *result2 = ft_strrchr(str, 'b');
	char *result3 = ft_strrchr(str, 'z');
	char *result4 = ft_strrchr(str, '\0');

	if (result1)
		printf("Dernier 'o' : %s\n", result1); // affiche "our"
	if (result2)
		printf("Dernier 'b' : %s\n", result2); // affiche "bonjour"
	if (result3 == NULL)
		printf("'z' non trouvé\n");
	if (result4)
		printf("Fin de chaîne (\\0) : '%s'\n", result4); // affiche chaîne vide ""

	return (0);
}
*/
