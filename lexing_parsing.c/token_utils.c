#include "pipex.h"

char	*ft_remove_quote(char *token)
{
	int		i;
	int		j;
	char	quote;
	char	*new;

	if (!token)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(token) + 1));
	if (!new)
		return (NULL);
	while (token[i])
	{
		/* Backslash handling : outside single quotes, backslash escapes next char */
		if (token[i] == '\\')
		{
			if (quote == '\'')
			{
				/* In single quotes, backslash is literal */
				new[j++] = token[i++];
			}
			else if (quote == '"')
			{
				/* In double quotes, check if next char is escapable */
				i++;
				if (token[i] && (token[i] == '"' || token[i] == '\\' || token[i] == '$'))
					new[j++] = token[i++];
				else if (token[i])
				{
					new[j++] = '\\';
					new[j++] = token[i++];
				}
			}
			else
			{
				/* Outside quotes, backslash escapes next char */
				i++;
				if (token[i])
					new[j++] = token[i++];
			}
		}
		/* Quote handling */
		else if ((token[i] == '\'' || token[i] == '"') && !quote)
		{
			quote = token[i];
			i++;
		}
		else if (token[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
		{
			new[j++] = token[i++];
		}
	}
	new[j] = '\0';
	return (new);
}