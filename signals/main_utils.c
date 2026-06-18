/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 00:00:00 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/15 00:00:00 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	**copy_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env && env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	init_shell(t_shell *shell, char **env)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->env = copy_env(env);
	shell->exit_code = 0;
	shell->saved_stdin = dup(STDIN_FILENO);
	if (shell->saved_stdin == -1)
	{
		perror("dup");
		return ;
	}
	shell->saved_stdout = dup(STDOUT_FILENO);
	if (shell->saved_stdout == -1)
	{
		close(shell->saved_stdin);
		perror("dup");
		return ;
	}
}
