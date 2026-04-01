#include "pipex.h"

int		ft_putchar(char c)
{
	return(write(1, &c, 1));
}
int		ft_putstr(char *str)
{
	int	i;

	if (!str)
		return(-1);
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return(0);
}