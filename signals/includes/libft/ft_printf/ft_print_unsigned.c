/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 20:45:57 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/01/21 15:46:58 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar(char c)
{
	return ((int)write(1, &c, 1));
}

static int	ft_unsigned(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb >= 10)
		count += ft_unsigned(nb / 10);
	count += ft_putchar(nb % 10 + '0');
	return (count);
}

int	ft_print_unsigned(unsigned int nb)
{
	return (ft_unsigned(nb));
}

/*
int main(void)
{
    ft_print_unsigned(0);
    write(1, "\n", 1);

    ft_print_unsigned(-1);
    write(1, "\n", 1);

    ft_print_unsigned(9);
    write(1, "\n", 1);

    ft_print_unsigned(-10);
    write(1, "\n", 1);

    ft_print_unsigned(99);
    write(1, "\n", 1);

    ft_print_unsigned(100);
    write(1, "\n", 1);

    ft_print_unsigned(4294967295);
    write(1, "\n", 1);

    ft_print_unsigned(777777777);

    return (0);
}*/
