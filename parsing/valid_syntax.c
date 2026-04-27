/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:20:16 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/04/26 16:12:50 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Parcourir la liste chainee jusqu'a la fin et regarder chaque noeud :
While (token != NULL)


REGLES :
- if le premier noeud est de type PIPE = error
- if dernier noeud est de type PIPE = error (ex : next==NULL)
- if double PIPE = error (ex : un PIPE a pour ptr next un autre PIPE)
- if un noeud est une REDIR et que le noeud sivant n'est pas 
	de type WORD = error (ex : next==NULL ou next!=WORD)


SI ERREUR :
   - free memoire // TODO garbage_collector
   - interompre processus
   - shell affiche nouveau prompt via readline
   	sans quitter le programme principal
   - affichage : bash: syntax error near unexpected token '...'
RETOUR : definir $? a 2
return (1);
ou
return (NULL);


WARNING :
PAS de exit sinon notre minishell se ferme completement
PAS de malloc
*/

void	print_error(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		i++;
	write(2, str, i);
}

int	error_syntax(char *token_value)
{
	print_error("bash: syntax error near unexpected token '");
	if (token_value)
		print_error(token_value);
	else
		print_error("newline");
	print_error("'\n");
	// TODO: Mettre a jour $? = 2
	// TODO: Appeler garbage_collector() pour nettoyer la liste
	return (1);
}

int	is_redirection(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == HEREDOC || type == APPEND);
}

int	valid_syntax(t_token *token)
{
	t_token	*current;

	if (!token)
		return (error_syntax(NULL)); // A voir si je return pas juste NULL
	if (token->type == PIPE)
		return (error_syntax(token->value));
	current = token;
	while (current != NULL)
	{
		if (current->type == PIPE)
		{
			if (current->next == NULL || current->next->type == PIPE)
				return (error_syntax("|"));
		}
		else if (is_redirection(current->type))
		{
			if (current->next == NULL)
				return (error_syntax(NULL));
			else if (current->next->type != WORD)
				return (error_syntax(current->next->value));
		}
		current = current->next;
	}
	return (0);
}
