/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:46:15 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/17 12:16:36 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_isalnum("hello wolrd"));
	printf("%d\n", ft_isalnum("helLO wolRd"));
	printf("%d\n", ft_isalnum("hello wolrd 42"));
	printf("%d\n", ft_isalnum("hello wo!rd"));
	printf("%d\n", ft_isalnum("1 hello wolrd  "));
}*/
