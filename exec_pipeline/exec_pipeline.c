#include "pipex.h"
#include <fcntl.h>
#include <sys/wait.h>

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

int    ft_first_cmds(t_px *px, int i)
{
    pid_t   pid;

    if (!px)
        return (1);
    pipe(px->pipefd);
    pid = fork();
    if (pid < 0)
        return;
    if (pid == 0)
    {
        dup2(px->fd_relai, 0);
        dup2(px->pipefd[1], 1);
        close(px->fd_relai);
        close(px->pipefd[1]);
        close(px->pipefd[0]);
        close(px->file.outfile_fd);
        execve(px->cmds[i].path, px->cmds[i].ready_execve, px->envp);
        perror(px->cmds[i].ready_execve[0]);
        _exit(px); 
    }
    close(px->fd_relai);
    close(px->pipefd[1]);
    px->fd_relai = px->pipefd[0];
    return(0);
}

int    ft_middle_cmd(t_px *px, int i)
{
    pid_t   pid;

    if (!px)
        return (-1);
    pipe(px->pipefd);
    pid = fork();
    if (pid < 0)
        return;
    if (pid == 0)
    {
        dup2(px->fd_relai, 0);
        dup2(px->pipefd[1],1);
        close(px->fd_relai);
        close(px->pipefd[1]);
        close(px->pipefd[0]);
        close(px->file.outfile_fd);
        execve(px->cmds[i].path, px->cmds[i].ready_execve, px->envp);
        perror(px->cmds[i].ready_execve[0]);
        _exit(px);
    }
    close(px->fd_relai);
    close(px->pipefd[1]);
    px->fd_relai = px->pipefd[0];
    return(1);
}
int    ft_last_cmd(t_px *px, int i)
{
    pid_t   pid;

    if (!px)
        return (-1);
    pid = fork();
    if (pid == 0)
    {
        dup2(px->fd_relai, 0);
        dup2(px->file.outfile_fd, 1);
        close(px->fd_relai);
        close(px->file.outfile_fd);
        execve(px->cmds[i].path, px->cmds[i].ready_execve, px->envp);
        perror(px->cmds[i].ready_execve[0]);
        _exit(px);
    }
    close(px->fd_relai);
    close(px->file.outfile_fd);
}

