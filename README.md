
Penser a faire un garbage malloc

typedef struct s_gc
{
    void    *ptr;
    t_gc    *next;
}   t_gc;



PENSER A CA !!!
C. Le nom du fichier temporaire Heredoc Dans ta structure t_redir, tu utilises char *file.

typedef struct s_redir
{
	t_token_type	type;
	char			*file;  // Contient le délimiteur pour un HEREDOC
	struct s_redir	*next;
}	t_redir;

Pour le HEREDOC (<<), les données sont généralement lues avant l'exécution des fork() et stockées dans un fichier temporaire caché (ex: /tmp/.heredoc_1)
. Il faudra juste t'assurer que, lors de la phase de préparation des Heredocs, tu remplaces le contenu de redir->file (qui contient le délimiteur) par le chemin absolu de ce fichier temporaire caché, pour que ton apply_redir puisse faire open(redir->file, O_RDONLY) de manière transparente.
