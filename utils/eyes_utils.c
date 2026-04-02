#include "pipex.h"

int		ft_is_sep(char c)
{
	return(c == ' ' || c == '\t');
}

int		ft_is_quote(char c)
{
	return (c == '\'');
}
t_char_type		ft_get_char_type(char c)
{
	if (c == ' ' || c == '\t')
		return (CHAR_SEP);
	if (c == '\'')
		return (CHAR_QUOTE);
	else 
		return(CHAR_OTHER);
}
void	ft_fill_matrix(t_state (*tab)[3])
{
	tab[0][0] = STATE_NORMAL;
	tab[0][1] = STATE_IN_QUOTE ;
	tab[0][2] = STATE_NORMAL;
	tab[1][0] = STATE_IN_QUOTE;
	tab[1][1] = STATE_NORMAL;
	tab[1][2] = STATE_IN_QUOTE;
}
int		ft_skip_separators(char *raw, int *i)
{
	if (!raw | !i)
		return(-1);
	while (raw[*i] && ft_is_sep(raw[*i]))
		(*i)++;
	return(1);
}