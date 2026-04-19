#include "pipex.h"

void     ft_init_struct_px_in_stack(t_px *px)
{
    if (!px)
        return;
    px->fd_relai = 0;
    px->nb_cmds = 0;
    px->is_here_doc = 0;
    px->cmds = NULL;
    px->envp = NULL;
    px->pipefd[0] = 0;
    px->pipefd[1] = 0;
    px->exit_code = 0;
}
void    ft_init_struct_file_in_stack(t_px *px)
{
    if (!px)
        return;
    px->file.infile = NULL;
    px->file.outfile = NULL;
    px->file.infile_fd = 0;
    px->file.outfile_fd = 0;
}

int     ft_open_fill(t_px *px, char **argv)
{
    if (!px || !argv)
        return(1);

    if (px->is_here_doc == 1)
    {
        px->file.outfile = argv[px->argc - 1];
        px->file.outfile_fd = open(px->file.outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (px->file.outfile_fd < 0)
            return (perror(px->file.outfile), ft_exit_px(px), 1);
        return (0);
    }
    px->file.infile = argv[1];
    px->file.infile_fd = open (px->file.infile, O_RDONLY);
    if (px->file.infile_fd < 0)
        perror(px->file.infile);
    px->file.outfile = argv[px->argc - 1];
    px->file.outfile_fd = open(px->file.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (px->file.outfile_fd < 0)
        return (perror(px->file.outfile), ft_exit_px(px), 1);
    return(0);
}

int   ft_fill_and_intialise_struct_px(char **argv, char **envp, int nb_cmd, t_px *px)
{
    if (!argv || !envp || !px || nb_cmd < 2 )
        return (1);

    ft_init_struct_px(px);
    ft_init_struct_file_in_stack(px);
    px->envp = envp;
    if (ft_is_here_doc(argv) == 1)
        px->is_here_doc = 1;
    if (ft_open_fill(&px, argv) == 1)
        return (1);
    ft_fill_and_intialise_struct_cmds_in_heap(px);
    return(0);
}   
