/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:56:56 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/14 13:02:21 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_isascii("1"));
	printf("%d\n", ft_isascii("P"));
	printf("%d\n", ft_isascii("	"));
	printf("%d\n", ft_isascii("~"));
	printf("%d\n", ft_isascii(" "));
}*/
