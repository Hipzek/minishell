/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 22:13:48 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 22:37:36 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_num_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

static int	check_exit_arg(t_shell *shell, t_cmd *cmd, long long *exit_code)
{
	int	overflow_err;

	if (is_numeric(cmd->args[1]) == 0)
	{
		print_num_error(cmd->args[1]);
		clean_and_exit(shell, 2);
	}
	overflow_err = 0;
	*exit_code = ft_atoll(cmd->args[1], &overflow_err);
	if (overflow_err == 1)
	{
		print_num_error(cmd->args[1]);
		clean_and_exit(shell, 2);
	}
	if (cmd->args[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	ft_exit(t_shell *shell, t_cmd *cmd)
{
	long long	exit_code;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd->args[1] == NULL)
		clean_and_exit(shell, shell->exit_code);
	exit_code = 0;
	if (check_exit_arg(shell, cmd, &exit_code) == 1)
		return (1);
	clean_and_exit(shell, (unsigned char)exit_code);
	return (0);
}
