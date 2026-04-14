#include "pipex.h"

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