/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:29:46 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/14 16:22:28 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	const char *str = "Bonjour";

	char *result1 = ft_strchr(str, 'j');
	char *result2 = ft_strchr(str, 'z');
	char *result3 = ft_strchr(str, '\0');

	if (result1)
		printf("Trouvé : %s\n", result1); // affiche "jour"
	else
		printf("Pas trouvé\n");

	if (result2)
		printf("Trouvé : %s\n", result2);
	else
		printf("Pas trouvé\n"); // affiche "Pas trouvé"

	printf("Fin de la chaîne : '%s'\n", result3); // affiche chaîne vide ""

	return (0);
}*/
