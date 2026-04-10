/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:18:13 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/01/21 15:47:10 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(char *str)
{
	int	i;

	if (!str)
		return (write(1, "(null)", 6));
	i = 0;
	while (str[i])
	{
		(write(1, &str[i], 1));
		i++;
	}
	return (i);
}

/*
int	main(void)
{
    ft_print_str("ABC");
    ft_print_str("\n");
    ft_print_str(NULL);
    ft_print_str("\n");
    ft_print_str("Test   espaces, caractères spéciaux !@#$%^&*()");
    ft_print_str("\n");
    ft_print_str("");
    ft_print_str("\n");
    return (0);
}*/
