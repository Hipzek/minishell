/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 13:43:14 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/04/26 18:07:53 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// getenv("PATH") -> split sur ':'
// pour chaque dir : dir + "/" + cmd
// access(path, X_OK) -> return path si OK
// Penser a si jamais envp est supp a renvoyer une erreur

static char	**get_path_from_env(char **envp)
{
	int		i;
	char	*path_value;
	char	**paths;

	if (!envp)
		return (NULL);
	i = 0;
	path_value = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_value = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static void	free_path(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char	*search_in_path(char **paths, char *cmd)
{
	char	*candidate;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		candidate = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!candidate)
			return (NULL);
		if (access(candidate, X_OK) == 0)
			return (candidate);
		free(candidate);
		i++;
	}
	return (NULL);
}

char	*path(char *cmd, char **envp)
{
	char	**paths;
	char	*found_path;

	if (!cmd || !envp)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = get_path_from_env(envp);
	// TODO gerer le cas d'erreur si on supp le PATH
	if (!paths)
		return (NULL);
	found_path = search_in_path(paths, cmd);
	free_path(paths);
	return (found_path);
}

/*
// ------------------- TEST --------------------

int main(int argc, char **argv, char **envp)
{
	char *res;

	(void)argc;
	(void)argv;

	printf("=== TEST PATH MINISHELL ===\n\n");

	// TEST 1 : commande simple
	res = path("ls", envp);
	printf("ls -> %s\n", res ? res : "NULL");
	free(res);

	// TEST 2 : commande inexistante
	res = path("commande_inexistante", envp);
	printf("fake -> %s\n", res ? res : "NULL");
	free(res);

	// TEST 3 : chemin absolu
	res = path("/bin/ls", envp);
	printf("/bin/ls -> %s\n", res ? res : "NULL");
	free(res);

	// TEST 4 : avec slash relatif
	res = path("./a.out", envp);
	printf("./a.out -> %s\n", res ? res : "NULL");
	free(res);

	// TEST 5 : PATH NULL simulé
	char *fake_envp[] = {
		"USER=test",
		"HOME=/home/test",
		NULL
	};

	res = path("ls", fake_envp);
	printf("ls (no PATH) -> %s\n", res ? res : "NULL");
	free(res);

	printf("\n=== FIN TEST ===\n");

	return 0;
}
*/
