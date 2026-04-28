/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:36:57 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/04/28 14:31:57 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
1. Affiche tous les args separes par un espace + saut de line (\n)
2. Flag -n supp le \n
3. Accepte les flags combines (ex : -nnnnnnn)
4. Plusieurs flags peuvent egalement se suivre (ex : echo -nnn -n -nnnn hello)
5. Si un arg (flag) ne respecte pas la lettre n arret
   et le reste est affiche comme du texte
*/

static int	is_valid_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	if (str[1] != 'n')
		return (0);
	i = 2;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	valid_flag;

	i = 1;
	valid_flag = 1;
	while (args[i] != NULL && is_valid_flag(args[i]))
	{
		valid_flag = 0;
		i++;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (valid_flag == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

/* ------------ TEST --------------
int	main(void)
{
	char	*args[] = {"echo", "-n", "-nnnn", "-n", "hello", NULL};

	ft_echo(args);
	return (0);
}*/
