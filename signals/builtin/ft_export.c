/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 11:30:52 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 22:37:43 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Vérifie si la chaîne jusqu'au signe '=' (ou jusqu'à la fin) 
est un nom de variable Bash valide
Renvoie 1 si valide ou 0 si invalide
*/

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i = 1;
	while (str[i] != '\0' && str[i] != '=' )
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static int	process_export_arg(t_shell *shell, char *arg)
{
	char	*equal_sign;
	char	*name;
	char	*value;

	if (is_valid_identifier(arg) == 1)
	{
		ft_putstr_fd("minishell: export: '", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign != NULL)
	{
		name = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
		update_env(shell, name, value);
		free(name);
		free(value);
	}
	else
		update_env(shell, arg, NULL);
	return (0);
}

int	ft_export(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	exit_status;

	if (cmd->args[1] == NULL)
		return (print_sorted_env(shell));
	exit_status = 0;
	i = 1;
	while (cmd->args[i] != NULL)
	{
		if (process_export_arg(shell, cmd->args[i]) == 1)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
