/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 07:43:19 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/17 12:17:17 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_isalpha(" hello wolrd "));
	printf("%d\n", ft_isalpha(" hello wolrd *     "));
	printf("%d\n", ft_isalpha(" hello wolrd !"));
	printf("%d\n", ft_isalpha(" hellO wolrd"));
}*/
