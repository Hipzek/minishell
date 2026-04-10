/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:23:30 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/01/21 15:47:13 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar(char c)
{
	return ((int)write(1, &c, 1));
}

static int	ft_puthex(unsigned long n)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		count += ft_puthex(n / 16);
	count += ft_putchar(base[n % 16]);
	return (count);
}

int	ft_print_ptr(void *ptr)
{
	int				count;
	unsigned long	ptr_l;

	if (!ptr)
		return (write(1, "(nil)", 5));
	ptr_l = (unsigned long)ptr;
	count = 0;
	count += write(1, "0x", 2);
		count += ft_puthex(ptr_l);
	return (count);
}

/*
int	main(void)
{
	ft_print_ptr(0);
	write(1, "\n", 1);
	
	ft_print_ptr(1);
	write(1, "\n", 1);
	
	ft_print_ptr(15);
	write(1, "\n", 1);
	
	ft_print_ptr(-16);
	write(1, "\n", 1);
	
	ft_print_ptr(255);
	write(1, "\n", 1);
	
	ft_print_ptr(48879);
	write(1, "\n", 1);
	
	ft_print_ptr(0xFFFFFFFFFFFFFFFF);
	return (0);
}*/
