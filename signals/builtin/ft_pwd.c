/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 14:35:02 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 22:37:51 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
PWD (Print Working Directory)
-> Repertoire de travail courant (current working directory)

Utilisation de la fonction getcwd qui accepte deux arguments :
- un pointeur vers un buffer (tableau de caractères)
- et sa taille
cette fonction regarde i-node (identifiant unique) du dossier actuel
et remonte jusqu'a la racine
*/

#include "../includes/minishell.h"

int	ft_pwd(t_shell *shell, t_cmd *cmd)
{
	char	*cwd;

	(void)shell;
	if (cmd->args[1] != NULL && cmd->args[1][0] == '-')
	{
		ft_putstr_fd("pwd: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
		return (2);
	}
	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

/* --------------- TEST ----------------
int	main(void)
{
	char	*args[] = {"pwd", NULL};
	char	*args2[] = {"pwd", "-k", NULL};

	ft_pwd(args);
	printf("\nTest valide et test erreur\n\n");
	ft_pwd(args2);
	return (0);
}*/
