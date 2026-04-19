#include "pipex.h"

void	ft_init_cmds(t_px *px)
{
	int	i;

    if (!px)
        return;
	i = 0;
	while (i < px->nb_cmds)
	{
		px->cmds[i].raw = NULL;
		px->cmds[i].ready_execve = NULL;
		px->cmds[i].path = NULL;
		px->cmds[i].status = CMD_INIT;
		px->cmds[i].exit_code = 0;
		px->cmds[i].resolv_mode = RESOLV_INIT;
		px->cmds[i].name = NULL;
        i++;
	}
}
int   ft_malloc_cmds(t_px *px)
{
    if (!px)
        return (1);
    px->cmds = (t_cmds *) malloc(sizeof(t_cmds) * (px->nb_cmds));
    if (!px->cmds)
        return (1);
    return(0);
}

void	ft_free_cmds(t_px *px)
{
	int	i;
	int	j;

	if (!px || !(px->cmds))
		return ;
	i = 0;
	while (i < px->nb_cmds)
	{
		if (px->cmds[i].ready_execve)
		{
			j = 0;
			while (px->cmds[i].ready_execve[j])
			{
				free(px->cmds[i].ready_execve[j]);
				j++;
			}
			free(px->cmds[i].ready_execve);
		}
		if (px->cmds[i].path)
			free(px->cmds[i].path);
		i++;
	}
    free(px->cmds);
}
int     ft_fill_and_intialise_struct_cmds_in_heap(t_px *px)
{
    if (!px)
        return(1);
    if (!(px.cmds = ft_malloc_cmds(px)))
	    return (ft_putstr("BUG AU MALLOC de CMDS\n"), 1);
    ft_init_cmds(px);
    if (ft_populate_and_norm(px) < 0)
	    return (ft_free_cmds(px), ft_putstr("BUG AVEC POPULATE\n"), 1);
    return (0);
}