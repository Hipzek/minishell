/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 02:50:30 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 02:50:32 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static int	ft_process_export_arg(t_shell *shell, char *arg)
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
		if (ft_process_export_arg(shell, cmd->args[i]) == 1)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
