#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef enum    e_char_type
{
    CHAR_SEP,
    CHAR_QUOTE,
    CHAR_OTHER
}   t_char_type;

typedef enum    e_cmd_status
{
    CMD_OK,
    CMD_EMPTY,
    CMD_NOT_FOUND,
    CMD_NO_PERMISSION,
    CMD_BUILD_ERROR,
    CMD_INIT
}   t_cmd_status;

typedef enum    e_resolv_path
{
    RESOLV_INIT,
    RESOLV_DIRECT,
    RESOLV_PATH,
    RESOLV_NONE
}   t_resolv_path;

typedef enum    e_state
{
    STATE_NORMAL,
    STATE_IN_QUOTE
}   t_state;
 
typedef struct s_cmd {
    char            *raw;           // Ex: "ls -l "
    char            **ready_execve; // Ex: ["ls", "-l", NULL] (sans les quotes !)
    char            *path;
    t_cmd_status    status;
    int             exit_code;
    t_resolv_path   resolv_mode;
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
void     ft_init_cmds(t_cmd *cmds, int nb_cmds);
char	**ft_split_almost_like_shell(char *raw);
t_cmd   *ft_malloc_cmds(int nb_cmds);
int     ft_populate_and_norm(t_cmd *cmds, char **argv, char **envp, int nb_cmds);
void        ft_free_paths(char **paths);
char	**ft_really_fill_paths(char **envp);
char	*ft_fill_path(char **envp);
char	**ft_fill_paths(char *path);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
int	 ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_with_slash(char const *s1, char const *s2);
void	ft_free_cmds(t_cmd *cmds, int nb_cmds);
char	*ft_remove_quote(char *token);
t_cmd_status	ft_get_cmd_status(t_cmd *cmds);
char	*ft_extract_path(char *cmds_from_ready_execve, char **paths);

#endif
