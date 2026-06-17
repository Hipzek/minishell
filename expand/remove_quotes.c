/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <hbelleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 15:43:24 by hbelleuv          #+#    #+#             */
/*   Updated: 2026/06/17 22:20:20 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*clean_token_value(char *str)
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
		else
			res = ft_strjoin_char(res, str[i]);
		i++;
	}
	return (res);
}

void	remove_quotes(t_shell *shell)
{
	t_token	*current;
	char	*cleaned_str;

	current = shell->token;
	while (current != NULL)
	{
		if (current->token_type == WORD)
		{
			cleaned_str = clean_token_value(current->value);
			free(current->value);
			current->value = cleaned_str;
		}
		current = current->next;
	}
}
