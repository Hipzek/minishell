/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 08:39:19 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/14 13:57:31 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_isdigit("123"));
	printf("%d\n", ft_isdigit("123444#"));
	printf("%d\n", ft_isdigit(" 12333 "));
	printf("%d\n", ft_isdigit("hello"));
}*/
