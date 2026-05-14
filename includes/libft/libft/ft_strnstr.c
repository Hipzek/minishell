/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:25:46 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/14 14:41:41 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && i + j < len && big[i + j] == little[j])
			j++;
		if (!little[j])
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	const char	*text = "Bonjour les étudiants de 42!";
	char		*result;

	result = ft_strnstr(text, "étudiants", 30);
	if (result)
		printf("Trouvé : \"%s\"\n", result);
	else
		printf("Pas trouvé !\n");

	result = ft_strnstr(text, "étudiants", 10);
	if (result)
		printf("Trouvé : \"%s\"\n", result);
	else
		printf("Pas trouvé !\n");

	return (0);
}
*/
