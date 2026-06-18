/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:36:57 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 22:37:21 by hbelleuv         ###   ########.fr       */
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

int	ft_echo(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	print_newline;

	(void)shell;
	i = 1;
	print_newline = 1;
	while (cmd->args[i] != NULL && is_valid_flag(cmd->args[i]))
	{
		print_newline = 0;
		i++;
	}
	while (cmd->args[i] != NULL)
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (print_newline == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
