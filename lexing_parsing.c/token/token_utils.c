#include "pipex.h"


int		ft_find_token_end(char *raw, int start)
{
	t_state			matrix[2][3];
	t_state			state;
	t_char_type		type;
	int				i;

	ft_fill_matrix(matrix);
	state = STATE_NORMAL;
	i = start;
	while (raw[i])
	{
		type = ft_get_char_type(raw[i]);
		if (type == CHAR_SEP && state == STATE_NORMAL)
			break;
		state = matrix[state][type];
		i++;
	}
	if (raw[i] == '\0' && state == STATE_IN_QUOTE)
		return (-1);
	return(i);
}
int		ft_count_token(char *raw)
{
	t_state			matrix[2][3];
	t_state			state;
	t_char_type		type;
	int				i;
	int				count;

	ft_fill_matrix(matrix);
	i = 0;
	count = 0;
	if (!raw || !raw[i])
		return(-1);
	while (raw[i])
	{
		ft_skip_separators(raw, &i);
		if (!raw[i])
			break;
		count++;
		state = STATE_NORMAL;
		while(raw[i])
		{
			type = ft_get_char_type(raw[i]);
			if (type == CHAR_SEP && state == STATE_NORMAL)
				break;
			state = matrix[state][type];
			i++;
		}
	if (raw[i] == '\0' && state == STATE_IN_QUOTE)
		return (-1);
	}
	return(count);
}


char	*ft_extract_token(char *raw, int *i)
{
	int		start;
	int		end;
	char	*token;

	if (!raw || !raw[*i] || !ft_skip_separators(raw, i))
		return(NULL);
	if (!raw[*i])
		return(NULL);
	start = *i;
	end = ft_find_token_end(raw, start);
	if (end == -1)
		return(NULL);
	token = ft_substr(raw, start, end - start);
	if (!token)
		return(NULL);
	*i = end;
	return(token);
}

void	ft_clean_tab(char **tab, int j)
{
	int		k;

	if (!tab)
		return;
	k = 0;
	while (k < j)
	{
		free(tab[k]);
		k++;
	}
	free(tab);
}

char	**ft_split_almost_like_shell(char *raw)
{
	char	**tab;
	char	*token;
	int		i;
	int		j;
	int		count;

	count = ft_count_token(raw);
	if (count == -1)
		return(NULL);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return(NULL);
	i = 0;
	j = 0;
	while (j < count)
	{
		token = ft_extract_token(raw, &i);
		if (!token || !(token = ft_remove_quote(token)))
			return (ft_clean_tab(tab, j), NULL);
		tab[j++] = token;
	}
	tab[j] = NULL;
	return(tab);
}

char	*ft_remove_quote(char *token)
{
	int		i;
	int		j;
	char	quote;
	char	*new;

	if (!token || !(new = malloc(ft_strlen(token) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (token[i])
	{
		if ((token[i] == '\'' || token[i] == '"') && !quote)
			quote = token[i];
		else if (token[i] == quote)
			quote = 0;
		else
			new[j++] = token[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}
