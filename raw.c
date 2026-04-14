#include "pipex.h"
/*
int	main(int argc, char **argv)
{
	char			*raw;
	int				i;
	t_state			matrix[2][3];
	t_state			state;
	int				start;
	int				end;
	t_char_type		type;
	

	ft_fill_matrix(&matrix[0]);
	if (argc < 2)
	return(ft_putstr("nb de parametre insufisant"), 0);
	raw = argv[1];
	i = 0;
	if (!ft_skip_separators(raw, &i))
		return(ft_putstr("erreur avec raw[i] et rendu  visible avec ft_skip_separator"), 0);
	if (!raw[i])
		return(ft_putstr("que des espaces"), 0);
	start = i;
	state = STATE_NORMAL;

	while (raw[i])
	{
		type = ft_get_char_type(raw[i]);
		if (state == STATE_NORMAL && type == CHAR_SEP)
			break;
		state = matrix[state][type];
		i++;
	}
	if (raw[i] == '\0' && state == STATE_IN_QUOTE)
		return(ft_putstr("fin de la string detecte alors que la state_machine est toujours engage avec une quote non ferme"), 0);
	end = i;
	write(1, raw + start, (end - start));
	return(0);
}

*/