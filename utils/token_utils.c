#include "pipex.h"

int	ft_skip_token(char *raw, int *i, t_state matrix[2][3])
{
	t_state	state;

	state = STATE_NORMAL;
	while (raw[*i] && ft_get_char_type(raw[*i]) != CHAR_SEP)
	{
		state = matrix[state][ft_get_char_type(raw[*i])];
		(*i)++;
	}
	if (raw[*i] == '\0' && state == STATE_IN_QUOTE)
		return (-1);
	return (0);
}

int	ft_count_token(char *raw)
{
	t_state	matrix[2][3];
	int		i;
	int		count;

	if (!raw || !raw[i])
		return (-1);
	ft_fill_matrix(matrix);
	i = 0;
	count = 0;
	while (raw[i])
	{
		ft_skip_separators(raw, &i);
		if (!raw[i])
			break ;
		if (ft_skip_token(raw, &i, matrix) == -1)
			return (-1);
		count++;
	}
	return (count);
}
