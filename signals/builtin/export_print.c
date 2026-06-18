/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 00:00:00 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 22:36:48 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_export_line(char *env_str)
{
	int		i;
	char	*equal_sign;

	equal_sign = ft_strchr(env_str, '=');
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	if (equal_sign != NULL)
	{
		i = 0;
		while (env_str + i <= equal_sign)
			ft_putchar_fd(env_str[i++], STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		ft_putstr_fd(equal_sign + 1, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd(env_str, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

static void	sort_env_ptrs(char **tab, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	print_sorted_env(t_shell *shell)
{
	int		count;
	int		i;
	char	**sorted;

	if (!shell || !shell->env)
		return (1);
	count = 0;
	while (shell->env[count])
		count++;
	sorted = malloc(sizeof(char *) * (count + 1));
	if (!sorted)
		return (1);
	i = -1;
	while (++i < count)
		sorted[i] = shell->env[i];
	sorted[count] = NULL;
	sort_env_ptrs(sorted, count);
	i = -1;
	while (++i < count)
		print_export_line(sorted[i]);
	free(sorted);
	return (0);
}
