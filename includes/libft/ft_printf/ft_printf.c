/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:40:31 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/01/21 15:46:55 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	ap;

	if (!format)
		return (-1);
	va_start(ap, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_print_type(format[i], ap);
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}

/*
int main(void)
{
    ft_printf("Hello %s !\n", "world");
    ft_printf("Number = %d\n", 42);
    ft_printf("Hex = %x\n", 255);
    ft_printf("Pointer = %p\n", (void*)1234);
    ft_printf("Percent = %%\n");
}*/
