#include "pipex.h"

int	main(int argc, char **argv)
{
	char	*raw;
	int		i;
	char	in_quote;

	if (argc < 2)
		return(ft_putstr("nb de parametre insufisant"), 0);
	raw = argv[1];
	i = 0;
	in_quote = 0;
	while (raw[i])
	{
		if (ft_is_quote(raw[i]))
		{
			if (in_quote == 0)
				in_quote = raw[i];
			else if (raw[i] == in_quote)
				in_quote = 0;
			ft_putchar('&');
		}
		else if (ft_is_sep(raw[i]) && in_quote == 0)
			ft_putchar('*');
		else
			ft_putchar(raw[i]);
		i++;
	}
	return(0);
}

int		ft_get_char_type(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '\'')
		return (2);
	else 
		return(3);
}



/*

		if (raw[i] == '\'' || raw[i] == )
		if (ft_is_sep(raw[i]) == 1)
		{
			ft_putchar('*');
		}
		else if (ft_is_quote(raw[i]) == 1)
		{
			ft_putchar('&');
		}
		else 
			ft_putchar(raw[i]);
		i++;
	}
	return(0);
}
*/