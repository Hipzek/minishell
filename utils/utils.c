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


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	len_s;
	size_t	space;
	size_t	a_copier;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if ((size_t)start >= len_s)
		return (ft_strdup(""));
	space = len_s - (size_t)start;
	if (len < space)
		a_copier = len;
	else
		a_copier = space;
	p = ft_calloc(a_copier + 1, sizeof * p);
	if (p == NULL)
		return (NULL);
	ft_memcpy(p, s + start, a_copier);
	p[a_copier] = '\0';
	return (p);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			total;
	size_t			i;

	if (size != 0 && (count > (SIZE_MAX / size)))
		return (NULL);
	total = count * size;
	p = malloc(total);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < total)
	{
		p[i] = '\0';
		i++;
	}
	return ((void *)(p));
}

