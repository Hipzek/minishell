/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:14:00 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 22:37:10 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
cd doit etre executer dans le parent car si
il s'execute dans un fork(), enfant alors le ne se deplacera pas reellement

Utilisation de chdir : chdir(const char *pathname)
return 0 en succes et -1 en erreur 
(si dossier existe pas ou erreur de permissions)

3 cas :
- Cas standard : cd /tmp ou cd srcs change de répertoire

- Cas "Trop d'arguments" : Si l'utilisateur tape cd srcs objs
Bash n'y va pas et affiche l'erreur bash: cd: too many arguments
et le code de retour devient 1

- Cas sans argument (Le fallback $HOME) : 

Si l'utilisateur tape cd tout seul, le shell doit récupérer
la valeur de la variable HOME dans l'environnement
et l'utiliser comme destination

Si la variable HOME a été supprimée (par ex: unset HOME)
cd doit afficher l'erreur bash: cd: HOME not set
*/

#include "../includes/minishell.h"

static char	*get_cd_path(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	if (cmd->args[1] != NULL && cmd->args[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (NULL);
	}
	if (cmd->args[1] == NULL)
	{
		path = get_env(shell, "HOME");
		if (path == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
		return (path);
	}
	return (cmd->args[1]);
}

int	ft_cd(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	path = get_cd_path(shell, cmd);
	if (path == NULL)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		perror("cd");
		free(old_pwd);
		return (1);
	}
	if (old_pwd)
		update_env(shell, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
		update_env(shell, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}
