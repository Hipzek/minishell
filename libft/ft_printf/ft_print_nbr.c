/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:37:23 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/01/21 15:47:20 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar(char c)
{
	return ((int)write(1, &c, 1));
}

static int	ft_putnbr(long nbr)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		count += ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr >= 10)
		count += ft_putnbr(nbr / 10);
	count += (ft_putchar((nbr % 10) + '0'));
	return (count);
}

int	ft_print_nbr(int nb)
{
	return (ft_putnbr((long)nb));
}

/*
int main(void)
{
    ft_print_nbr(0);
    write(1, "\n", 1);

    ft_print_nbr(1);
    write(1, "\n", 1);

    ft_print_nbr(-1);
    write(1, "\n", 1);

    ft_print_nbr(2147483647);
    write(1, "\n", 1);

    ft_print_nbr(-2147483648);
    write(1, "\n", 1);

    ft_print_nbr(1000000000);
    write(1, "\n", 1);

    ft_print_nbr(-99999999);

    return (0);
}*/
