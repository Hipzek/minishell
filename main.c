#include "pipex.h"

int	ft_populate_and_norm(t_cmd **cmds, char **argv, char **envp, int nb_cmds)
{
	int	i;

	if (!cmds || !argv || nb_cmds < 2)
		return (-1);
    // SI ON EST EN MODE HERE_DOC alors on commence le parsing a partir de i = 1 
    // HORS BONUS, argv[0] == "pipex", argv[1] == "file1", argv[2] == "cmd1" 
    // et argv[argc - 2] == "cmd finale" : argv[argc - 1] == "file2"
    // POUR LE PRECISER : argv[argc] == segfault car on commence a compter a partir de 0
    // DANS LE CAS DU BONUS : " pipex(0) here_doc(1) limiter(2) CMD1(3)..." 
	i = 0;
	while (i < nb_cmds)
	{
		(*cmds)[i].raw = argv[i + 2];
        (*cmds)[i].ready_execve = ft_split_almost_like_shell((*cmds)[i].raw);
		if (!(*cmds)[i].ready_execve)
			return (-1);
		if ((*cmds)[i].ready_execve[0] != NULL)
		{
			(*cmds)[i].path = ft_extract_path((*cmds)[i].ready_execve[0], envp);
			if ((*cmds)[i].path != NULL)
				(*cmds)[i].status = CMD_OK;
			else
				(*cmds)[i].status = CMD_NOT_FOUND;
		}
		else
			(*cmds)[i].status = CMD_EMPTY;
		i++;
	}
	return (0);
}
int	main(int argc, char **argv, char **envp)
{
	int		nb_cmds;
    t_px    *px;
    
    if (argc < 5)
		return (ft_putstr("nb de parametre insufisant\n"), 1);
    if (ft_is_here_doc(argv) == 1) 
	    nb_cmds = argc - 4;
    else
        nb_cmds = argc - 3;
    px = ft_fill_px(argv, envp, nb_cmds);
    if (!px) 
        return(1);
	if (!(px->cmds = ft_malloc_cmds(nb_cmds)))
		return (ft_putstr("BUG AU MALLOC de CMDS\n"), 1);
	ft_init_cmds(px);
	if (ft_populate_and_norm(&(px->cmds), argv, envp, nb_cmds) < 0)
		return (ft_free_cmds(px->cmds, nb_cmds), free(px->cmds), ft_putstr("BUG AVEC POPULATE\n"), 1);
    ft_exec_pipeline(px);
    ft_free_cmds(px);
    ft_free_px(px);
	return (0);
}
int     ft_is_here_doc(char **argv)
{
    if (!argv)
        return(-1);
    if (ft_strncmp(argv[1], "here_doc", 5) == 0)
        return (1);
    return(0);
}

int     ft_exec_pipeline(t_px *px)
{
    int     i;

    if (!px)
        return(-1);
    px->fd_relai = ft_first_cmds(&px, 0);
    i = 1;
    while (i < (px->nb_cmds - 1))
    {
        px->fd_relai = ft_middle_cmd(&px, i);
        i++;
    }
    px->fd_relai = ft_last_cmd(&px, i);
    return (1);
}

int    ft_first_cmds(t_px **px, int i)
{
    pid_t   pid;

    if (!px)
        return (-1);
    pipe((*px)->pipefd);
    pid = fork();
    if (pid < 0)
        return;
    if (pid == 0)
    {
        dup2((*px)->fd_relai, 0);
        dup2((*px)->pipefd[1], 1);
        close((*px)->fd_relai);
        close((*px)->pipefd[1]);
        close((*px)->pipefd[0]);
        close((*px)->outfile_fd);
        execve((*px)->cmds[i].path, (*px)->cmds[i].ready_execve, (*px)->envp);
        perror((*px)->cmds[i].ready_execve[0]);
        _exit(127); 
    }
    close((*px)->fd_relai);
    close((*px)->pipefd[1]);
    return((*px)->pipefd[0]);
}

int    ft_middle_cmd(t_px **px, int i)
{
    pid_t   pid;

    if (!px)
        return (-1);
    pipe((*px)->pipefd);
    pid = fork();
    if (pid < 0)
        return;
    if (pid == 0)
    {
        dup2((*px)->fd_relai, 0);
        dup2((*px)->pipefd[1],1);
        close((*px)->fd_relai);
        close((*px)->pipefd[1]);
        close((*px)->pipefd[0]);
        close((*px)->outfile_fd);
        execve((*px)->cmds[i].path, (*px)->cmds[i].ready_execve, (*px)->envp);
        perror((*px)->cmds[i].ready_execve[0]);
        _exit(127);
    }
    close((*px)->fd_relai);
    close((*px)->pipefd[1]);
    return ((*px)->pipefd[0]); 
}
int    ft_last_cmd(t_px **px, int i)
{
    pid_t   pid;

    if (!px)
        return (-1);
    pid = fork();
    if (pid == 0)
    {
        dup2((*px)->fd_relai, 0);
        dup2((*px)->outfile_fd, 1);
        close((*px)->fd_relai);
        close((*px)->outfile_fd);
        execve((*px)->cmds[i].path, (*px)->cmds[i].ready_execve, (*px)->envp);
        perror((*px)->cmds[i].ready_execve[0]);
        _exit(127);
    }
    close((*px)->fd_relai);
    close((*px)->outfile_fd);
}



/*
    pipe(pipefd);
    pid = fork();
    if (pid < 0)
        return;
    if (pid == 0)
    {
        dup2(fd_relai, 0);
        dup2(pipefd[1], 1);
        close(fd_relai);
        close(pipefd[1]);
        close(pipefd[0]);
        close(outfile_fd);
        execve(cmds[i].path, cmds[i].ready_execve[0], NULL);
        perror(cmds[i].ready_execve[0]);
        exit(127);
    }
    ≈
    close(pipefd[1]);
    fd_relai = pipefd[0];
    i++;
    while (i < nb_cmds - 1)
    {
        pipe(pipefd);
        pid = fork();
        if (pid < 0)
            return;
        if (pid == 0)
        {
            dup2(fd_relai, 0);
            dup2(pipefd[1],1);
            close(fd_relai);
            close(pipefd[1]);
            close(pipefd[0]);
            close(outfile_fd);
            execve(cmds[i].path, cmds[i].ready_execve[0], NULL);
            perror(cmds[i].ready_execve[0]);
            exit(127);
        }
        close(fd_relai);
        close(pipefd[1]);
        fd_relai = pipefd[0];
        i++;
    }
    pid = fork();
    if (pid == 0)
    {
        dup2(fd_relai, 0);
        dup2(outfile_fd, 1);
        close(fd_relai);
        close(outfile_fd);
        execve(cmds[i].path, cmds[i].ready_execve[0], NULL);
        perror(cmds[i].ready_execve[0]);
    }
    close(fd_relai);
    close(outfile_fd);

}
```


