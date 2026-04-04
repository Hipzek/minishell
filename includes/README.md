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


