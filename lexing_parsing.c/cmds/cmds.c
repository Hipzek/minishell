#include "pipex.h"

void	ft_init_cmds(t_cmd *cmds, int nb_cmds)
{
	int	i;

	i = 0;
	while (i < nb_cmds)
	{
		cmds[i].raw = NULL;
		cmds[i].ready_execve = NULL;
		cmds[i].path = NULL;
		cmds[i].status = CMD_INIT;
		cmds[i].exit_code = 0;
		cmds[i].resolv_mode = RESOLV_INIT;
		i++;
	}
}

t_cmd	*ft_malloc_cmds(int nb_cmds)
{
	t_cmd	*cmds;

	if (nb_cmds < 2)
		return (NULL);
	cmds = (t_cmd *)malloc(sizeof(t_cmd) * nb_cmds);
	if (!cmds)
		return (NULL);
	return (cmds);
}

void	ft_free_cmds(t_cmd *cmds, int nb_cmds)
{
	int	i;
	int	j;

	if (!cmds)
		return ;
	i = 0;
	while (i < nb_cmds)
	{
		if (cmds[i].ready_execve)
		{
			j = 0;
			while (cmds[i].ready_execve[j])
			{
				free(cmds[i].ready_execve[j]);
				j++;
			}
			free(cmds[i].ready_execve);
		}
		if (cmds[i].path)
			free(cmds[i].path);
		i++;
	}
}
