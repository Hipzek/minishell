#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>

typedef enum    e_char_type
{
    CHAR_SEP,
    CHAR_QUOTE,
    CHAR_OTHER
}   t_char_type;

typedef enum    e_state
{
    STATE_NORMAL,
    STATE_IN_QUOTE
}   t_state;

typedef struct s_cmd {
    char    *raw;           // Ex: "ls -l "
    char    **ready_execve; // Ex: ["ls", "-l", NULL] (sans les quotes !)
    char    *path;
    int     is_valid;          // Ex: "/bin/ls"
} t_cmd;

int		ft_putchar(char c);
int		ft_putstr(char *str);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);


int		ft_is_sep(char c);
int	    ft_is_quote(char c);
t_char_type	ft_get_char_type(char c);
void	ft_fill_matrix(t_state (*tab)[3]);
int		ft_skip_separators(char *raw, int *i);
int		ft_find_token_end(char *raw, int start);
int		ft_count_token(char *raw);
char	*ft_extract_token(char *raw, int *i);

char	**ft_split_almost_like_shell;

#endif
