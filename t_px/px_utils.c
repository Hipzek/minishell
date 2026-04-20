#include "pipex.h"

void     ft_init_struct_px_in_stack(t_px *px)
{
    if (!px)
        return;
    px->fd_relai = -1;
    px->nb_cmds = 0;
    px->is_here_doc = 0;
    px->cmds = NULL;
    px->envp = NULL;
    px->pipefd[0] = -1;
    px->pipefd[1] = -1;
    px->exit_code = 0;
    px->argc = 0;
    px->argv = NULL;
}

void    ft_init_struct_file_in_stack(t_px *px)
{
    if (!px)
        return;
    px->file.infile = NULL;
    px->file.outfile = NULL;
    px->file.infile_fd = -1;
    px->file.outfile_fd = -1;
}

int     ft_open_fill(t_px *px)
{
    if (!px || !px->argv)
        return (1);
    if (px->is_here_doc == 1)
    {
        px->file.outfile = px->argv[px->argc - 1];
        px->file.outfile_fd = open(px->file.outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (px->file.outfile_fd < 0)
            return (perror(px->file.outfile), 1);
        return (0);
    }
    px->file.infile = px->argv[1];
    px->file.infile_fd = open(px->file.infile, O_RDONLY);
    if (px->file.infile_fd < 0)
        perror(px->file.infile);
    /* set fd_relai to infile fd so the first command can read from it */
    if (px->file.infile_fd >= 0)
        px->fd_relai = px->file.infile_fd;
    px->file.outfile = px->argv[px->argc - 1];
    px->file.outfile_fd = open(px->file.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (px->file.outfile_fd < 0)
    {
        if (px->file.infile_fd >= 0)
            close(px->file.infile_fd);
        return (perror(px->file.outfile), 1);
    }
    return (0);
}

int	ft_populate_and_norm(t_px *px)
{
    int	cmd_i;
    int arg_i;

    if (!px || !px->cmds || !px->argv)
        return (1);
    cmd_i = 0;
    arg_i = 2;
    if (px->is_here_doc == 1)
        arg_i = 3;
    while (cmd_i < px->nb_cmds)
    {
        px->cmds[cmd_i].raw = px->argv[arg_i];
        px->cmds[cmd_i].ready_execve = ft_split_almost_like_shell(px->cmds[cmd_i].raw);
        if (!px->cmds[cmd_i].ready_execve)
            return (1);
        if (!px->cmds[cmd_i].ready_execve[0])
            px->cmds[cmd_i].status = CMD_EMPTY;
        else
        {
            px->cmds[cmd_i].path = ft_extract_path(px->cmds[cmd_i].ready_execve[0], px);
            if (px->cmds[cmd_i].path)
                px->cmds[cmd_i].status = CMD_OK;
            else
            {
                px->cmds[cmd_i].status = CMD_NOT_FOUND;
                px->cmds[cmd_i].exit_code = 127;
            }
        }
        cmd_i++;
        arg_i++;
    }
    return (0);
}


int   ft_fill_and_intialise_struct_cmds_in_heap(t_px *px)
{
    if (!px)
        return (1);
    if (ft_malloc_cmds(px) == 1)
        return (perror("malloc"), 1);
    ft_init_cmds(px);
    if (ft_populate_and_norm(px) < 0)
        return (ft_free_cmds(px), 1);
    return (0);
}

int   ft_fill_and_intialise_struct_px(t_px *px, int argc, char **argv, char **envp)
{
    if (!px || !argv || !envp || argc < 5)
        return (1);
    ft_init_struct_px_in_stack(px);
    ft_init_struct_file_in_stack(px);
    px->argc = argc;
    px->argv = argv;
    px->envp = envp;
    px->is_here_doc = ft_is_here_doc(argv);
    if (px->is_here_doc == 1)
        px->nb_cmds = argc - 4;
    else
        px->nb_cmds = argc - 3;
    if (px->nb_cmds < 2)
        return (ft_putstr_fd("Error: Not enough commands\n", 2), 1);
    if (ft_open_fill(px) == 1)
        return (1);
    if (ft_fill_and_intialise_struct_cmds_in_heap(px) == 1)
        return (1);
    return (0);
}

void	ft_cleanup_px(t_px *px)
{
    if (!px)
        return;
    if (px->file.infile_fd >= 0)
        close(px->file.infile_fd);
    if (px->file.outfile_fd >= 0)
        close(px->file.outfile_fd);
    if (px->fd_relai >= 0)
        close(px->fd_relai);
    ft_free_cmds(px);
}


int   ft_malloc_cmds(t_px *px)
{
    if (!px)
        return (1);
    px->cmds = (t_cmd *) malloc(sizeof(t_cmd) * (px->nb_cmds));
    if (!px->cmds)
        return (1);
    return (0);
}

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

void	ft_free_cmds(t_px *px)
{
    int	i;
    int	j;

    if (!px || !(px->cmds))
        return;
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
    px->cmds = NULL;
}

/* Minimal helper: write a string to given fd (used by multiple places) */
int	ft_putstr_fd(char *str, int fd)
{
    if (!str)
        return (-1);
    while (*str)
    {
        write(fd, str, 1);
        str++;
    }
    return (0);
}

/* Minimal detection of here_doc: check argv[1] == "here_doc" */
int	ft_is_here_doc(char **argv)
{
    if (!argv || !argv[1])
        return (0);
    if (ft_strncmp(argv[1], "here_doc", 9) == 0)
        return (1);
    return (0);
}
