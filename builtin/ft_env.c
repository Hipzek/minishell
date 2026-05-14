/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 11:09:53 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/09 21:02:55 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
- doit afficher que les variables qui possèdent une valeur
(c'est-à-dire celles qui contiennent un signe =)
- Si on fait export HOLA (sans =) la variable existe dans Bash mais env ignore
*/

int	ft_env(t_shell *shell, t_cmd *cmd)
{
	int	i;

	(void)cmd;
	if (!shell || !shell->env)
		return (1);
	i = 0;
	while (shell->env[i] != NULL)
	{
		if (ft_strchr(shell->env[i], '=') != NULL)
		{
			ft_putstr_fd(shell->env[i], STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}
