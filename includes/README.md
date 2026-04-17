Jr duid fitrvyeur d'une unsine amazon 

J'ai un entrepot : le main pour compter les commandes

j'ai un netoyage intial avec avec la preparatopn desmcartpms

il y a le controle qualite  POPULATE AND CHECK

Oui.

Dans pipex, c’est bien à toi de coder cette logique.

Pas forcément sous le nom exact ft_get_path, mais tu dois fabriquer une fonction équivalente qui :

récupère PATH dans envp
découpe PATH avec :
construit des chemins possibles
teste chaque chemin avec access(..., X_OK)
renvoie le bon chemin pour execvei


Ajoute une fonction (par ex. dans exec.c) :
Prototype : int ft_exec_pipeline(t_cmd *cmds, int nb_cmds, char **envp, char *infile, char *outfile);
Elle fera l’ouverture in_fd/out_fd, construira pipes, forkera, executera, attendra enfants et retournera code final.



Je vais reprendre mon code pour etre sur de ne pas etre stupide et pour se faire j'ai besoin de l'ouvrir a plusieurs endroits
