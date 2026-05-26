/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:55:49 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/18 20:02:13 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
L'Expansion (Développement des $)
Cette étape doit se faire AVANT de supprimer les guillemets
-> car besoin des guillemets pour savoir si un $ doit être interprété ou non.

-> Réutiliser la Machine à États du Lexer (NORMAL, IN_SQUOTE, IN_DQUOTE) 
sur la chaîne value de chaque t_token.

L'algorithme caractère par caractère :

- Mode IN_SQUOTE : Le $ est un simple caractère littéral. On ne fait rien.
- Mode NORMAL ou IN_DQUOTE : Si vous croisez un $, 
vous devez extraire le nom de la variable
(qui se termine au premier caractère non-alphanumérique ou non-underscore)
Cherchez sa valeur dans shell->env et remplacez-la.
- Cas particulier $? : S'il est suivi d'un ?,
remplacez-le directement par la valeur de shell->exit_code.

PIÈGES :
Piège de la variable vide :

- Si l'utilisateur tape echo $VIDE (Mode NORMAL) : la variable est
remplacée par du vide,
le token entier doit être supprimé de votre liste.
- Si l'utilisateur tape echo "$VIDE" (Mode IN_DQUOTE) : le résultat est vide,
mais la chaîne vide "" doit être conservée comme un token valide.
- Le signe dollar isolé : Un $ suivi d'un espace ou d'une fin de chaîne (\0)
reste un caractère $ littéral.
*/

#include "../includes/minishell.h"

char	*append_var_value(t_shell *shell, char *res, char *str, int *i)
{
	char	*var_name;
	char	*var_value;
	int		start;
	char	*tmp;

	tmp = res;
	(*i)++; // saute le $
	// cas 1 : $?
	if (str[*i] == '?')
	{
		var_value = ft_itoa(shell->exit_code);
		res = ft_strjoin(tmp, var_value);
		free(var_value);
		free(tmp);
		(*i)++;
		return (res);
	}
	// cas 2 : variable env classique
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	var_value = get_env(shell, var_name);
	free(var_name);
	if (var_value != NULL)
	{
		res = ft_strjoin(tmp, var_value);
		free(tmp);
	}
	return (res);
}

int	is_valid_dollar(char c)
{
	// si fin de chaine, espace ou tabulation
	if (c == '\0' || c == ' ' || c == '\t')
		return (0);
	// si le char est squote ou dquote
	if (c == '"' || c == '\'')
		return (0);
	return (1);
}

static char	*process_expand(t_shell *shell, char *str)
{
	char	*res;
	t_state	state;
	int		i;

	res = ft_strdup("");
	state = NORMAL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && state == NORMAL)
			state = IN_SQUOTE;
		else if (str[i] == '\'' && state == IN_SQUOTE)
			state = NORMAL;
		else if (str[i] == '"' && state == NORMAL)
			state = IN_DQUOTE;
		else if (str[i] == '"' && state == IN_DQUOTE)
			state = NORMAL;
		if (str[i] == '$' && state != IN_SQUOTE && is_valid_dollar(str[i + 1]))
		{
			res = append_var_value(shell, res, str, &i);
		}
		else
		{
			res = ft_strjoin_char(res, str[i]);
			i++;
		}
	}
	return (res);
}

t_token	*del_token_node(t_token **head, t_token *prev, t_token *to_del)
{
	t_token	*next_node;

	next_node = to_del->next;
	if (prev == NULL)
		*head = next_node;
	else
		prev->next = next_node;
	if (to_del->value)
		free(to_del->value);
	free(to_del);
	return (next_node);
}

void	expand_tokens(t_shell *shell)
{
	t_token	*current;
	t_token	*prev;
	char	*new_val;

	current = shell->token;
	prev = NULL;
	while (current != NULL)
	{
		if (current->token_type == WORD)
		{
			// 1 creation nouvelle chaine
			new_val = process_expand(shell, current->value);
			// 2 si expand vide
			if (new_val && *new_val == '\0' && !has_quotes(current->value))
			{
				free(new_val);
				current = del_token_node(&shell->token, prev, current);
				continue ;
			}
			free(current->value);
			current->value = new_val;
		}
		prev = current;
		current = current->next;
	}
}
