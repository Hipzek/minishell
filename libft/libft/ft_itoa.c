/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:48:37 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/17 16:23:36 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_chiffre(int n)
{
	int	nb;

	nb = 0;
	if (n <= 0)
		nb = 1;
	while (n != 0)
	{
		n = n / 10;
		nb++;
	}
	return (nb);
}

char	*ft_itoa(int n)
{
	int		len;
	long	nb;
	char	*str;

	nb = n;
	len = nb_chiffre(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[--len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}

/*
#include <stdio.h>
int	main(void)
{
	char *s1 = ft_itoa(0);
	char *s2 = ft_itoa(42);
	char *s3 = ft_itoa(-12345);

	printf("s1 = '%s'\n", s1);
	printf("s2 = '%s'\n", s2);
	printf("s3 = '%s'\n", s3);

	free(s1);
	free(s2);
	free(s3);
	return (0);
}
*/
