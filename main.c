#include "pipex.h"

int     main(int argc, char **argv, char **envp)
{
    int             nb_cmds;
	int				i;
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

int     ft_populate_and_norm(t_cmd *cmds, char **argv, char **envp int nb_cmds)
{
    int i;

    if (!cmds || !argv || nb_cmds < 2)
        return (-1);
    i = 0;
    while (i < nb_cmds)
    {
        cmds[i].raw = argv[i + 2]; 
        cmds[i].ready_execve = ft_split_almost_like_shell(cmds[i].raw);
        if (!cmds[i].ready_execve)
            return (-1); // je le traite dans le main
        if (cmds[i].ready_execve[0] != NULL)
        {
            cmds[i].path = ft_extract_path(cmds[i].ready_execve[0], envp);
            if (cmds[i].path != NULL)
                cmds[i].is_valid = 1;
            else
                cmds[i].is_valid = 0;
        }
        else
            cmds[i].is_valid = 0
        i++;
    }
    return (0);
}
t_cmds      **
void     ft_init_cmds(t_cmd *cmds, int nb_cmds);

t_cmd   *ft_malloc_cmds(int nb_cmds)
{
    t_cmd   *temp_cmds;

    if (nb_cmds < 2)
        return (NULL);
    temp_cmds = (t_cmd *)malloc(sizeof(t_cmd) * (nb_cmds + 1));
    if (!temp_cmds)
        return (NULL);
    return (temp_cmds);
}

t_cmd    *argv_to_cmds(char **argv, int argc)
{
    char    *temp_cmds;
    int     nb_cmds;

    2 . fill cmds et utilisation du split et du remove quote et creation d un premier filtre a merde
    3 . Pour bien commencer ft_init_cmds
    4.  creation de la fonction get_to_ready_execve avec la fonction access et un split a : et le test sil y a  deja 
    5 .
}


t_cmd     *ft_fill_cmds_from_argv(t_cmd *cmd, char **tab)
{
    int     i;
    cmd

}

il faut d'abord trouver parhnamew
En faisant split (pathname, ":") jobtiens 
**path ou path[0] = " /bin" et il faut ensuite le joindre avec /
je met ca dans une chaine de caractete *test par exemple
Si accecc fonctionne, ca retourne 0 et alors je 
on teste chaque bout de path[i] avec accec
Tant qu'on est pas arrive au dernier ou que path est toujours null, on continuer de testet
Quand LE NOMBRE DE chemin est atteint et que path est toujours nul de la streuture 
on peut arreter car une fonction ne fonctionne pas sinon on passe a la commande sujivamte dispo dans la premiere chaine de commande.ready execve

 je pars de envp, cours sur ca please, je trouve path, je cree une variable qui va recevoir path car le path de la structure
  n'est rempl que si on touve sinon il; reste a 0, je le met dans *path, ce *path j'en fais avec split **paths. nouvelle boucle, tant que path[j] et que cmds.path == NULL,
 on continu, si fin de path et toujours null, ca veut dire aucun chemin pour l'executio, dans la boucle on a fait acces question sur la double condition avec ||
  dans access ou pas, puis meme chose et a chaque fin de travail dans le boucle imbirque du while ou free bien sur ce dernier, on ne l'utilise que ici bien sur voir, 
  fais deux fonctions pour deiux mission mission de test et mission de preparation de chaque commande au test


    Il faut verifier que les 5 premieres lettres
    es

    char**envp

    char    *path_value;
    char    **paths;
    char    *candidate;
    char    *found;

    if (strchr(cmds[].ready_execve[0]),'/')
    {

    }
  while (envp[i])
  {
    if (ft_strncmp("envp[i]", "PATH=", 5) == 0)
    {
        path = strdup[envp[i + 5]];
        break;
    }
    i++;
    if (!path_value)
        return(NULL);

  }

{)


/*
	if (argc < 2)
	return(ft_putstr("nb de parametre insufisant"), 0);
	raw = argv[1];
	i = 0;
	if (!ft_skip_separators(raw, &i))
		return(ft_putstr("erreur avec raw[i] et rendu  visible avec ft_skip_separator"), 0);
	if (!raw[i])
		return(ft_putstr("que des espaces"), 0);
	start = i;
	state = STATE_NORMAL;

	while (raw[i])
	{
		type = ft_get_char_type(raw[i]);
		if (state == STATE_NORMAL && type == CHAR_SEP)
			break;
		state = matrix[state][type];
		i++;
	}
	if (raw[i] == '\0' && state == STATE_IN_QUOTE)
		return(ft_putstr("fin de la string detecte alors que la state_machine est toujours engage avec une quote non ferme"), 0);
	end = i;
	write(1, raw + start, (end - start));
	return(0);
}