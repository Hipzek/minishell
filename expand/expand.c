/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:55:49 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 19:46:28 by hbelleuv         ###   ########.fr       */
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

static char	*ft_handle_spaces(char *res, char *str, int *i)
{
	int	space_count;

	space_count = 0;
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
	{
		space_count++;
		(*i)++;
	}
	if (space_count > 0)
		res = ft_strjoin_char(res, ' ');
	return (res);
}

static char	*reduce_spaces(char *str)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			res = ft_handle_spaces(res, str, &i);
		else
		{
			res = ft_strjoin_char(res, str[i]);
			i++;
		}
	}
	return (res);
}

static void	expand_exit_code(t_expand *exp)
{
	char	*var_value;
	char	*tmp;

	tmp = exp->res;
	var_value = ft_itoa(exp->shell->exit_code);
	exp->res = ft_strjoin(tmp, var_value);
	free(var_value);
	free(tmp);
	exp->i++;
}

static void	expand_normal_var(t_expand *exp)
{
	char	*var_name;
	char	*var_value;
	char	*processed_value;
	char	*tmp;
	int		start;

	tmp = exp->res;
	start = exp->i;
	while (exp->str[exp->i] && (ft_isalnum(exp->str[exp->i])
			|| exp->str[exp->i] == '_'))
		exp->i++;
	var_name = ft_substr(exp->str, start, exp->i - start);
	var_value = get_env(exp->shell, var_name);
	free(var_name);
	if (var_value == NULL)
	{
		exp->res = tmp;
		return ;
	}
	if (exp->state == NORMAL)
	{
		processed_value = reduce_spaces(var_value);
		exp->res = ft_strjoin(tmp, processed_value);
		free(processed_value);
	}
	else
		exp->res = ft_strjoin(tmp, var_value);
	free(tmp);
}

void	ft_append_dollar_expansion(t_expand *exp)
{
	exp->i++;
	if (exp->str[exp->i] == '?')
		expand_exit_code(exp);
	else if (ft_isalpha(exp->str[exp->i]) || exp->str[exp->i] == '_')
		expand_normal_var(exp);
}

int	is_valid_dollar(char c)
{
	if (c == '\0' || c == ' ' || c == '\t')
		return (0);
	if (c == '"' || c == '\'')
		return (0);
	return (1);
}

void	ft_update_quote_state(char c, t_state *state)
{
	if (c == '\'' && *state == NORMAL)
		*state = IN_SQUOTE;
	else if (c == '\'' && *state == IN_SQUOTE)
		*state = NORMAL;
	else if (c == '"' && *state == NORMAL)
		*state = IN_DQUOTE;
	else if (c == '"' && *state == IN_DQUOTE)
		*state = NORMAL;
}
