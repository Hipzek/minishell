#include "pipex.h"
#include <sys/stat.h>

char	**ft_really_fill_paths(char **envp)
{
	int		i;
	char	*path_value;
	char	**paths;

	if (!envp)
		return (NULL);
	i = 0;
	path_value = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_value = envp[i] + 5;
			break;
		}
		i++;
	}
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	return (paths);
}

void	ft_free_paths(char **paths)
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

char	*ft_extract_path(char *cmd, char **envp)
{
	char	**paths;
	char	*candidate;
	int		i;

	if (!cmd || !envp)
		return (NULL);
	/* Check if command already contains a slash (direct path) */
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	/* Get all paths from PATH environment variable */
	paths = ft_really_fill_paths(envp);
	if (!paths)
		return (NULL);
	/* Search command in each path directory */
	i = 0;
	while (paths[i])
	{
		candidate = ft_strjoin_with_slash(paths[i], cmd);
		if (!candidate)
		{
			ft_free_paths(paths);
			return (NULL);
		}
		if (access(candidate, X_OK) == 0)
		{
			ft_free_paths(paths);
			return (candidate);
		}
		free(candidate);
		i++;
	}
	ft_free_paths(paths);
	return (NULL);
}
