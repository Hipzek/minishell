#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
    t_px	px;
    int		exit_code;

    if (argc < 5)
    {
        ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 ... outfile\n", 2);
        return (1);
    }
    
    exit_code = ft_fill_and_intialise_struct_px(&px, argc, argv, envp);
    if (exit_code == 1)
    {
        ft_cleanup_px(&px);
        return (1);
    }
    
    exit_code = ft_exec_pipeline(&px);
    ft_cleanup_px(&px);
    return (exit_code);
}
