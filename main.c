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
		return (ft_free_cmds(cmds, nb_cmds), free(cmds), 
				ft_putstr("BUG AVEC POPULATE\n"), 1);
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

int	ft_exec_pipeline(t_cmd *cmds, int nb_cmds, char *infile, char *outfile)
{
    int infile_fd;
    int outfile_fd;
    int tab[2];
    int fd_relai_source_dentree;

    infile_fd = open (infile, O_RDONLY);
    if (infile_fd < 0)
        return;
    
    outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile_fd < 0)
        return ;
    pipe(tab);
    fd_relai_source_dentree = infile_fd;
    fork
    if (pid == 0)
        appel fonction peemiere commande(cmds,relai, pipe1);
    if (pid > 0)
    on cl;ose les fd imiutiles
    on close le relai.

    i = 0;
    while (i < nb de commande)
    {
        pipe (tab);
        fd_relai_source_dentree = pipe[0];
        if (pid == 0)
            appel fonction deuxieme commande(cmds,relai, pipe1);
        if (pid > 0) 
            on close les fd
            on ferme le relai;
    }
    dernier forK
    la fonction 3

    waitpidd

    }
    }

    
    
        //fonction 1 pour premiere commande
        //fonction 2 pour les n commandes avant la derniere
        // fonction 3 pour la derniere

    
    fork

	return (0);
}

int first_cmd(t_cmd *cmds, int nb_cmds, int infile_fd, int fd_relai_source_dentree)
{

}

