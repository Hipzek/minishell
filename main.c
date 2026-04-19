#include "pipex.h"

int	ft_populate_and_norm(t_px *px)
{
	int	i;

	if (!px || !px->cmds)
		return (1);
    // SI ON EST EN MODE HERE_DOC alors on commence le parsing a partir de i = 1 
    // HORS BONUS, argv[0] == "pipex", argv[1] == "file1", argv[2] == "cmd1" 
    // et argv[argc - 2] == "cmd finale" : argv[argc - 1] == "file2"
    // POUR LE PRECISER : argv[argc] == segfault car on commence a compter a partir de 0
    // DANS LE CAS DU BONUS : " pipex(0) here_doc(1) limiter(2) CMD1(3)..." 
    if (px->is_here_doc == 1)
        i = 1;
    else
        i = 0
	while (i < px->nb_cmds nb)
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
    t_px    px;
    //encapsuler meme le test de base, faire juste init.px si 1, erreur et le return de la faction appelante 
    //ecriy sur .erreuu dans la struct ou putsr-fd ou perrot....
    ///ici il faut faire une operation pour retirer les test d'entre et avoir un main avec juste des appels de fonction un truc net 
    // px est ma variable de contexte 
    //
    if (argc < 5)
		return (ft_putstr_fd("nombres de parametre insufisant\n", 2), 1);
    px.is_here_doc = ft_is_here_doc(argv);
    if (px.is_here_doc == 1)
	    px.nb_cmds = argc - 4;
    else
        px.nb_cmds = argc - 3;
    px.argc = argc;
    px.envp = envp;
    px.argv = argv;
    if (px.is_here_doc == 1 && argc < 6)
        return (ft_putstr_fd("Erreur : arguments insuffisants\n", 2), 1);
    if (ft_fill_px(&px, argv, envp, nb_cmds) < 1)
        return(1);
    if (ft_exec_pipeline(&px) < 0)
        return(ft_free_cmds(&px), 1);
    ft_free_cmds(&px);
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
