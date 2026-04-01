#include "pipex.h"

int		ft_is_sep(char c)
{
	if (c == ' ' || c == '\t')
		return(1);
	else
		return(0);
}

int		ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return(1);
	else
		return(0);
}
