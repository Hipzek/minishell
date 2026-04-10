/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 13:25:58 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/04/10 18:38:46 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;	

	int	status;

	char	*line;
	line = readline("minishell > ");
	int	i = 0;
	while (i < 10)
	{
		line = readline("minishell > ");
		if (line == NULL)
			break;
		printf("%s", line);
		if (fork() == 0)
			execvp(argv[1], argv + 1);
		free(line);
		i++;
	}

	wait(&status);

	return (EXIT_SUCCESS);
}
*/

int	main(void)
{
    char *line;      // contiendra la ligne saisie par l'utilisateur
    int status;      // stocke le statut du processus enfant (retour de la commande)

    // boucle infinie → comportement classique d'un shell
    while (1)
    {
        // affiche le prompt et attend une entrée utilisateur
        line = readline("minishell > ");
        // si readline retourne NULL (Ctrl+D), on quitte le shell
        if (!line)
            break;
        // si la ligne n'est pas vide (ex: juste ENTER ne compte pas)
        if (*line)
            add_history(line); // on ajoute la commande à l'historique

        // PARSING : découpage de la commande

        char *args[100]; // tableau de pointeurs vers les arguments
        int i = 0;
        // strtok découpe la chaîne "line" en mots séparés par des espaces
        char *token = strtok(line, " ");
        // boucle pour récupérer tous les mots
        while (token)
        {
            args[i++] = token;        // on stocke chaque mot
            token = strtok(NULL, " "); // NULL → continuer sur la même chaîne
        }
        args[i] = NULL; // très important : fin du tableau pour execvp

        // EXECUTION DE LA COMMANDE

        // on vérifie qu'il y a bien une commande (ex: "ls")
        if (args[0])
        {
            pid_t pid = fork(); // création du processus enfant
            if (pid == 0)
            {
                // PROCESSUS ENFANT
		// remplace le programme courant par la commande demandée
                execvp(args[0], args);
                // si execvp échoue, on arrive ici
                perror("execvp"); // affiche l'erreur système
                exit(1);          // termine le processus enfant avec erreur
            }
            else if (pid > 0)
            {
                // PROCESSUS PARENT
                // attend que l'enfant se termine
                waitpid(pid, &status, 0);
            }
            else
            {
                // ERREUR FORK
		perror("fork"); // fork a échoué
            }
	}
        // libération de la mémoire allouée par readline
        free(line);
    }
    return (0);
}
