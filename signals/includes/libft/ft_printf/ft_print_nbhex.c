/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbhex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:51:23 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/01/21 15:47:22 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar(char c)
{
	return ((int)write (1, &c, 1));
}

static int	ft_puthex(unsigned int n, char format)
{
	int		count;
	char	*base;

	count = 0;
	if (format == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		count += ft_puthex(n / 16, format);
	}
	count += ft_putchar(base[n % 16]);
	return (count);
}

int	ft_print_nbhex(unsigned int n, char format)
{
	return (ft_puthex(n, format));
}

/*
int	main(void)
{
	ft_print_nbhex(0, 'x');
	write(1, "\n", 1);
	
	ft_print_nbhex(1, 'x');
	write(1, "\n", 1);
	
	ft_print_nbhex(9, 'x');
	write(1, "\n", 1);
	
	ft_print_nbhex(10, 'x');
	write(1, "\n", 1);
	
	ft_print_nbhex(-15, 'X');
	write(1, "\n", 1);
	
	ft_print_nbhex(-16, 'x');
	write(1, "\n", 1);
	
	ft_print_nbhex(255, 'x');
	write(1, "\n", 1);
	
	ft_print_nbhex(4095, 'X');
	write(1, "\n", 1);
	
	ft_print_nbhex(4294967295, 'x');
	write(1, "\n", 1); // unsigned max
	return (0);
}*/
