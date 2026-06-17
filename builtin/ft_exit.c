/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 22:13:48 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/29 10:28:44 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_num_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

static void	ft_parse_sign(char *str, int *i, int *sign)
{
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == 32)
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

long long	ft_atoll(char *str, int *error)
{
	unsigned long long	res;
	int					sign;
	int					i;

	res = 0;
	sign = 1;
	i = 0;
	ft_parse_sign(str, &i, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if ((sign == 1 && res > LLONG_MAX)
			|| (sign == -1 && res > (unsigned long long)LLONG_MAX + 1))
		{
			*error = 1;
			return (0);
		}
		i++;
	}
	return ((long long)res * sign);
}

/*
func clean_and_exit :
Doit free t_shell et appeler exit()
*/

int	ft_exit(t_shell *shell, t_cmd *cmd)
{
	long long	exit_code;
	int			overflow_err;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd->args[1] == NULL)
		clean_and_exit(shell, shell->exit_code);
	if (is_numeric(cmd->args[1]) == 0)
	{
		print_num_error(cmd->args[1]);
		clean_and_exit(shell, 2);
	}
	overflow_err = 0;
	exit_code = ft_atoll(cmd->args[1], &overflow_err);
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
	clean_and_exit(shell, (unsigned char)exit_code);
	return (0);
}
