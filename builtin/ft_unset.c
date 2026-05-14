/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 21:23:25 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/11 21:32:40 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	rm_env_var(t_shell *shell, int index)
{
	free(shell->env[index]);
	while (shell->env[index] != NULL)
	{
		shell->env[index] = shell->env[index + 1];
		index++;
	}
}

static int	is_valid_unset_id(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i = 1;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	j;
	int	len;
	int	exit_status;

	if (!shell || !shell->env || !cmd->args)
		return (1);
	exit_status = 0;
	i = 1;
	while (cmd->args[i] != NULL)
	{
		if (is_valid_unset_id(cmd->args[i]) == 1)
		{
			ft_putstr_fd("minishell: unset: '", STDERR_FILENO);
			ft_putstr_fd(cmd->args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			exit_status = 1;
		}
		else
		{
			len = ft_strlen(cmd->args[i]);
			j = 0;
			while (shell->env[j] != NULL)
			{
				if (ft_strncmp(shell->env[j], cmd->args[i], len) == 0
					&& shell->env[j][len] == '=')
				{
					rm_env_var(shell, j);
					break ;
				}
				j++;
			}
		}
		i++;
	}
	return (exit_status);
}
