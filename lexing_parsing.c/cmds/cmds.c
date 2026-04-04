#include "pipex.h"

void     ft_init_cmds(t_cmd *cmds, int nb_cmds);
{
    int     i;

    i = 0;
    while (i < nb_cmds)
    {
        cmds[i].raw = NULL;
        cmds[i].ready_execve = NULL;
        cmds[i].path = NULL;
        cmds[i].is_valid = 0;
        i++;
    }
}
