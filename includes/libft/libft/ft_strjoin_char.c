/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 13:29:23 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/16 13:32:34 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char *s, char c)
{
	char	*res;
	int		i;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!res)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	while (s[i] != '\0')
	{
		res[i] = s[i];
		i++;
	}
	res[i] = c;
	res[i+1] = '\0';
	free(s);
	return (res);
}
