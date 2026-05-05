/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 21:18:46 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/05/05 13:06:41 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Cherche une variable dans l'environnement et renvoie un pointeur 
sur sa valeur (sans allouer de nouvelle mémoire)
Renvoie NULL si la variable n'existe pas
*/

char	*get_env(t_shell *shell, char *name)
{
	int	i;
	int	len;

	if (!shell || !shell->env ||!name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (shell->env[i] != NULL)
	{
		// On compare le nom, ET on s'assure que le caractère suivant est '='
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& shell->env[i][len] == '=')
			// On renvoie l'adresse de la chaîne, en sautant le "NOM="
			return (shell->env[i] + len + 1);
		i++;
	}
	return (NULL);
}

// Fonction utilitaire pour créer la chaîne "NOM=VALEUR" allouée dynamiquement

static char	*create_env(char *name, char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

/*
Met à jour une variable existante ou la crée si elle n'existe pas
Renvoie 0 en cas de succès 1 en cas d'erreur de malloc
*/

int	update_env(t_shell *shell, char *name, char *value)
{
	int		i;
	int		len;
	char	*new_str;
	char	**new_env;

	if (!shell || !shell->env || !name || !value)
		return (1);
	new_str = creat_env(name, value);
	if (!new_str)
		return (1);
	len = ft_strlen(name);
	i = 0;
	// cas 1 : la variable existe donc on la remplace
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
				&& shell->env[i][len] == '=')
		{
			free(shell->env[i]); // libere NOM=ANCIEN
			shell->env[i] = new_str; // met le NOM=NOUVEAU
			return (0);
		}
		i++;
	}
	// Cas 2 : la variable existe pas -> il faut agrandir l'env
	// i contient le nb d'elements existants
	// on alloue : i elements + 1 pour le nouveau + 1 pour NULL
	new_env = malloc(sizeof(char *) * (i + 1) + 1);
	if (!new_env)
	{
		free(new_str);
		return (1);
	}
	// Copie des ptr existants
	i = 0;
	while (shell->env[i] != NULL)
	{
		new_env[i] = shell->env[i];
		i++;
	}
	// ajoue du nouveau + NULL
	new_env[i] = new_str;
	new_env[i + 1] = NULL;
	// libere l'ancien double tab et remplace par le nouveau
	free(shell->env);
	shell->env = new_env;
	return (0);
}
