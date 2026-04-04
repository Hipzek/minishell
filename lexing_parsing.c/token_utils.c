#include "pipex.h"

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

void     ft_init_cmds(t_cmd *cmds, int nb_cmds);
{
    int     i;

    i = 0;
    while (i < nb_cmds)
    {
        cmds[i].raw = NULL;
        cmds[i].ready_execve = NULL;
        cmds[i].path = NULL;
        cmds[i].is_valid = 0;
        i++;
    }
}


/* 
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
*/