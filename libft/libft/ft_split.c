/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelleuv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:57:31 by hbelleuv          #+#    #+#             */
/*   Updated: 2025/11/14 16:35:26 by hbelleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	in_word;
	int	count;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*alloc_dup_word(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static void	*ft_free(char **array, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		start;

	tab = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = -1;
	while (s[++j])
	{
		if (s[j] != c && (j == 0 || s[j - 1] == c))
			start = j;
		if (s[j] != c && (s[j + 1] == c || s[j + 1] == '\0'))
		{	
			tab[i] = alloc_dup_word(s, start, j + 1);
			if (!tab[i++])
				return (ft_free(tab, i));
		}
	}
	tab[i] = NULL;
	return (tab);
}

/*
#include <stdio.h>
int	main(void)
{
	char	**tab;
	int	i = 0;

	tab = ft_split("Hello World 42", ' ');
	if (!tab)
		return (1);

	while (tab[i])
	{
		printf("tab[%d] = '%s'\n", i, tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}
*/
