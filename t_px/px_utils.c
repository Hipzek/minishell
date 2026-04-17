#include "pipex.h"

t_px    *ft_init_and_malloc_struct(void)
{
    t_px    *px;

    px = malloc(sizeof(t_px));
    if (!px)
        return (NULL);
    px->file->infile = NULL;
    px->file->outfile = NULL;
    px->file->infile_fd = -1;
    px->file->outfile_fd = -1;
    px->fd_relai = -1;
    px->nb_cmds = 0;
    px->is_here_doc = 0;
    px->cmds = NULL;
    px->envp = NULL;
    px->pipefd[0] = -1;
    px->pipefd[1] = -1;
    return(px);
}

t_px   *ft_fill_px(char **argv, char **envp, t_cmd *cmds, int nb_cmd)
{
    t_px    *px;
    
    if (!argv || !envp || !cmds || !nb_cmd)
        return (NULL);
   
    px = ft_init_and_malloc_struct();
    px->file->infile = argv[1];
    px->file->outfile = argv[nb_cmd - 1];
    px->file->infile_fd = open(px->file->infile, O_RDONLY);
    if (px->file->infile_fd < 0)
        return (perror("open infile"), free(px), NULL);
    px->file->outfile_fd = open(px->file->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644 ); 
    if (px->file->outfile_fd < 0)
        return (perror("open outfile"), free(px), NULL);
    px->fd_relai = px->file->infile_fd;
    px->nb_cmds = nb_cmd;
    px->cmds = cmds;
    px->envp = envp;
    px->is_here_doc = 0;
    return(px);
}
