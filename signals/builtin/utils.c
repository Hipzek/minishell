/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 21:18:46 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 22:38:17 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*create_env(char *name, char *value)
{
	char	*tmp;
	char	*res;

	if (value == NULL)
		return (ft_strdup(name));
	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

static int	replace_env(t_shell *shell, char *name, char *new_str)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& (shell->env[i][len] == '='
			|| shell->env[i][len] == '\0'))
		{
			free(shell->env[i]);
			shell->env[i] = new_str;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	add_env(t_shell *shell, char *new_str)
{
	int		i;
	char	**new_env;

	i = 0;
	while (shell->env[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_str);
		return (1);
	}
	i = 0;
	while (shell->env[i] != NULL)
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[i] = new_str;
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

static int	env_var_exists(t_shell *shell, char *name)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& (shell->env[i][len] == '='
			|| shell->env[i][len] == '\0'))
			return (1);
		i++;
	}
	return (0);
}

int	update_env(t_shell *shell, char *name, char *value)
{
	char	*new_str;

	if (!shell || !shell->env || !name)
		return (1);
	if (value == NULL && env_var_exists(shell, name))
		return (0);
	new_str = create_env(name, value);
	if (!new_str)
		return (1);
	if (replace_env(shell, name, new_str) == 1)
		return (0);
	return (add_env(shell, new_str));
}
