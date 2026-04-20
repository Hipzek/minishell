#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

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

typedef struct s_file
{
    char    *infile;
    char    *outfile;
    int     infile_fd;
    int     outfile_fd;
} t_file;

typedef struct s_cmd {
    char            *raw;
    char            **ready_execve;
    char            *path;
    char            *name;
    t_cmd_status    status;
    int             exit_code;
    t_resolv_path   resolv_mode;
} t_cmd;

typedef struct  s_px {
    t_cmd   *cmds;
    t_file  file;
    int     is_here_doc;
    int     fd_relai;
    int     nb_cmds;
    char    **envp;
    char    **argv;
    int     pipefd[2];
    int     exit_code;
    int     argc;
} t_px;

typedef enum    e_state
{
    STATE_NORMAL,
    STATE_IN_QUOTE
}   t_state;

/* ===== UTILS ===== */
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putstr_fd(char *str, int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin_with_slash(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

/* ===== TOKENIZATION (LEXING) ===== */
int		ft_is_sep(char c);
int	    ft_is_quote(char c);
t_char_type	ft_get_char_type(char c);
void	ft_fill_matrix(t_state (*tab)[3]);
int		ft_skip_separators(char *raw, int *i);
int		ft_find_token_end(char *raw, int start);
int		ft_count_token(char *raw);
char	*ft_extract_token(char *raw, int *i);
char	**ft_split_almost_like_shell(char *raw);
char	*ft_remove_quote(char *token);

/* ===== COMMANDS (PARSING) ===== */
int     ft_malloc_cmds(t_px *px);
void    ft_init_cmds(t_px *px);
void	ft_free_cmds(t_px *px);
int     ft_fill_and_intialise_struct_cmds_in_heap(t_px *px);
int	ft_populate_and_norm(t_px *px);
t_cmd_status	ft_get_cmd_status(t_cmd *cmds);

/* ===== PATH RESOLUTION ===== */
void        ft_free_paths(char **paths);
char	**ft_really_fill_paths(char **envp);
char	*ft_fill_path(char **envp);
char	**ft_fill_paths(char *path);
char	*ft_extract_path(char *cmds_from_ready_execve, t_px *px);

/* ===== MAIN STRUCTURE (CONSTRUCTOR) ===== */
void    ft_init_struct_px_in_stack(t_px *px);
void    ft_init_struct_file_in_stack(t_px *px);
int     ft_open_fill(t_px *px);
int     ft_fill_and_intialise_struct_px(t_px *px, int argc, char **argv,
            char **envp);
void    ft_cleanup_px(t_px *px);
/* ===== EXECUTION PIPELINE ===== */
int     ft_exec_pipeline(t_px *px);
int     ft_first_cmds(t_px *px, int i);
int     ft_middle_cmd(t_px *px, int i);
int     ft_last_cmd(t_px *px, int i);

/* ===== HERE_DOC ===== */
int     ft_is_here_doc(char **argv);

#endif
