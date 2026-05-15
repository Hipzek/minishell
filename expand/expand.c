/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:55:49 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/15 22:09:45 by hbelleuv         ###   ########.fr       */
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
- Mode NORMAL ou IN_DQUOTE : Si vous croisez un $, vous devez extraire le nom de la variable
(qui se termine au premier caractère non-alphanumérique ou non-underscore). Cherchez sa valeur dans shell->env et remplacez-la.
- Cas particulier $? : S'il est suivi d'un ?, remplacez-le directement par la valeur de shell->exit_code.

PIÈGES :
Piège de la variable vide :

- Si l'utilisateur tape echo $VIDE (Mode NORMAL) : la variable est remplacée par du vide,
le token entier doit être supprimé de votre liste.
- Si l'utilisateur tape echo "$VIDE" (Mode IN_DQUOTE) : le résultat est vide,
mais la chaîne vide "" doit être conservée comme un token valide.
- Le signe dollar isolé : Un $ suivi d'un espace ou d'une fin de chaîne (\0) reste un caractère $ littéral.
*/

void	expand_tokens(t_shell *shell)
{
	...;
}
