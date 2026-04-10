/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:04:01 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/11 13:12:35 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}
/*
int main(void)
{
    int fd;

    ft_putnbr_fd(42, 1);
    ft_putchar_fd('\n', 1);

    ft_putnbr_fd(-12345, 1);
    ft_putchar_fd('\n', 1);

    fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd != -1)
    {
        ft_putnbr_fd(2025, fd);
        ft_putchar_fd('\n', fd);
        close(fd);
    }
    return (0);
}
*/
