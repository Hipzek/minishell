#include "pipex.h"

int     main(int argc, char **argv, char **envp)
{
    int             nb_cmds;
    t_cmd           *cmds;

    if (argc < 5)
	    return(ft_putstr("nb de parametre insufisant\n"), 0);
    
    nb_cmds = argc - 3;
    if (!(cmds = ft_malloc_cmds(nb_cmds)))
        return(ft_putstr("BUG AU MAlloc de CMDS\n"), 0);
    ft_init_cmds(cmds, nb_cmds);
    if (ft_populate_and_norm(cmds, argv, envp, nb_cmds) < 0)
        return (ft_free_cmds(cmds, nb_cmds), free(cmds),ft_putstr("BUG AVEC POPULATE\n"), 0); 

    return (0);
}

