/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:47:10 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/26 16:59:40 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
HEREDOC :

1. TOUS les Heredocs s'exécutent AVANT la moindre exécution de commande :
exemple : si cat << A | grep "bonjour" << B
Ne pas lancer de fork tout de suite
d'abord afficher > pour le document A puis le doc B
Et SEULEMENT ensuite lancer l'exec du pipeline

2. Le token qui suit le << est le dilimiteur (EOF)
Vis a vis des guillemets :
- SI le delimiteur n'a pas de guillemets :
  - il faut expand les $VAR a l'interieur du texte tape par l'utilisateur
- SI le dilimiteur a des guillemets simple ou double :
  - aucune expansion a faire

3. Signaux (Comportement specifique durant le heredoc)
- Ctrl + C : interrompt instantanement la lecture et la commande est annulee 
($? = 130)
- Ctrl + D : Pas un cas erreur ( == NULL , "EOF forcee") et garde le donc deja tapee
*/

#include "../includes/minishell.h"


/*
Verifie si la chaine contient des guillemets simples ou doubles
Renvoie 1 si vrai et 0 si faux
*/
int	has_quotes(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);

}

/*
Expand les $VAR d'env
guillemets ignoriees
*/

static char	*expand_heredoc_line(t_shell *shell, char *str)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	if (!str || !res)
		return (res);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_valid_dollar(str[i + 1]))
			res = append_var_value(shell, res, str, &i);
		else
		{
			res = ft_strjoin(res, &str[i]);
			i++;
		}
	}
	return (str);
}

// Lit l'entree utilisateur jusqu'au EOF et renvoie le fd de lecture (fd)
int	read_heredoc(t_shell *shell, char *delim_token)
{
	int		fd;
	int		expand_flag;
	char	*line;
	char	*real_delim;

	expand_flag = !has_quotes(delim_token);
	real_delim = clean_token_value(delim_token);
	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", real_delim);
			break ;
		}
		if (ft_strcmp(line, real_delim) == 0)
		{
			free(line);
			break ;
		}
		if (expand_flag)
			line = expand_heredoc_line(shell, line); // TODO
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(real_delim);
	close(fd);
	return (fd);
}
