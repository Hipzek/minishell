#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		nb_cmds;
	t_cmd	*cmds;

	if (argc < 5)
		return (ft_putstr("nb de parametre insufisant\n"), 1);
	
	nb_cmds = argc - 3;
	if (!(cmds = ft_malloc_cmds(nb_cmds)))
		return (ft_putstr("BUG AU MALLOC de CMDS\n"), 1);
	ft_init_cmds(cmds, nb_cmds);
	if (ft_populate_and_norm(cmds, argv, envp, nb_cmds) < 0)
		return (ft_free_cmds(cmds, nb_cmds), free(cmds), \
				ft_putstr("BUG AVEC POPULATE\n"), 1);
	
	/* TODO: Implement ft_exec_pipeline and file I/O */
	
	ft_free_cmds(cmds, nb_cmds);
	free(cmds);
	return (0);
}

int	ft_populate_and_norm(t_cmd *cmds, char **argv, char **envp, int nb_cmds)
{
	int	i;

	if (!cmds || !argv || nb_cmds < 2)
		return (-1);
	i = 0;
	while (i < nb_cmds)
	{
		cmds[i].raw = argv[i + 2];
		cmds[i].ready_execve = ft_split_almost_like_shell(cmds[i].raw);
		if (!cmds[i].ready_execve)
			return (-1);
		if (cmds[i].ready_execve[0] != NULL)
		{
			cmds[i].path = ft_extract_path(cmds[i].ready_execve[0], envp);
			if (cmds[i].path != NULL)
				cmds[i].status = CMD_OK;
			else
				cmds[i].status = CMD_NOT_FOUND;
		}
		else
			cmds[i].status = CMD_EMPTY;
		i++;
	}
	return (0);
}
