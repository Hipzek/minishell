/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 11:30:52 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/14 16:22:51 by hbelleuv         ###   ########.fr       */
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

// affichage formaté (declare -x NOM="VALEUR")

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

/*
Sans argument : export doit trier l'environnement par ordre alphabétique
et afficher avec "declare -x"  devant.
Avec arguments : export doit analyser chaque mot
vérifier s'il est valide et l'ajouter à l'environnement.


WARNING : si une variable est invalide, export affiche une erreur, 
change son code de retour à 1, mais NE S'ARRÊTE PAS

CAS 1 : Aucun argument (fonction de tri)
CAS 2 : pls arguments
*/

int	ft_export(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		exit_status;
	char	*equal_sign;
	char	*name;
	char	*value;

	if (cmd->args[1] == NULL)
		return (print_sorted_env(shell));
	exit_status = 0;
	i = 1;
	while (cmd->args[i] != NULL)
	{
		if (is_valid_identifier(cmd->args[i]) == 1)
		{
			ft_putstr_fd("minishell: export: '", STDERR_FILENO);
			ft_putstr_fd(cmd->args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			exit_status = 1;
		}
		else
		{
			equal_sign = ft_strchr(cmd->args[i], '=');
			if (equal_sign != NULL)
			{
				name = ft_substr(cmd->args[i], 0, equal_sign - cmd->args[i]);
				value = ft_strdup(equal_sign + 1);
				update_env(shell, name, value);
				free(name);
				free(value);
			}
		}
		i++;
	}
	return (exit_status);
}
