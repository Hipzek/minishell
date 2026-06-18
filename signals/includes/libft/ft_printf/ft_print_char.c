/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:56:48 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/01/21 15:47:28 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_char(char c)
{
	return ((int)write(1, &c, 1));
}

/*
int	main(void)
{
    ft_print_char('A');
    ft_print_char('\n');
    return 0;
}*/
