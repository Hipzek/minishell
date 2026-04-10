/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:04:58 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/17 12:13:09 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_isprint("\r"));
	printf("%d\n", ft_isprint("	"));
	printf("%d\n", ft_isprint(" "));
	printf("%d\n", ft_isprint("~"));
}*/
