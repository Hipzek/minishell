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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	p = malloc(len + 1);
	if (p == NULL)
		return (NULL);
	ft_memcpy(p, s, len);
	p[len] = '\0';
	return (p);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
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


static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	word;
	size_t	count;

	i = 0;
	word = 0;
	count = 0;
	while (s[i])
	{
		if (word == 0 && s[i] != c)
		{
			word = 1;
			count++;
		}
		else if (s[i] == c)
			word = 0;
		i++;
	}
	return (count);
}

static char	*ft_remplissage(char const *s, char c)
{
	char	*p;
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	p = ft_calloc(i + 1, sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static void	ft_free_all(char **p, size_t j)
{
	while (j > 0)
		free(p[--j]);
	free(p);
}

static int	ft_fill_split(char **p, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	word;

	i = 0;
	j = 0;
	word = 0;
	while (s[i])
	{
		if (word == 0 && s[i] != c)
		{
			p[j] = ft_remplissage(s + i, c);
			if (!p[j])
			{
				ft_free_all(p, j);
				return (-1);
			}
			j++;
			word = 1;
		}
		else if (s[i] == c)
			word = 0;
		i++;
	}
	return ((int)j);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		filled;

	if (!s)
		return (NULL);
	p = ft_calloc(ft_count_words(s, c) + 1, sizeof * p);
	if (!p)
		return (NULL);
	filled = ft_fill_split(p, s, c);
	if (filled < 0)
		return (NULL);
	p[filled] = NULL;
	return (p);
}

char    *ft_strjoin_with_slash(char const *s1, char const *s2)
{
	char    *p;
	size_t  len_s1;
	size_t  len_s2;
	size_t  len_total;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len_total = len_s1 + len_s2;
	p = ft_calloc(len_total + 2, sizeof * p);
	if (p == NULL)
		return (NULL);
	ft_memcpy(p, s1, len_s1);
	ft_memcpy(p + len_s1, "/", 1);
	ft_memcpy(p + len_s1 + 1, s2, len_s2);
	p[len_total + 1] = '\0';
	return (p);
}
