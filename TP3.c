/*

TP3: SYNCHRONISATION DES PROCESSUS, TUBES ET SIGNAUX

I - C’EST DU LOURD

1) Le processus père (le programme main) crée 500 processus fils, indicés de 0 à 499.

2) Ce programme affiche si l'on se trouve dans le processus père ou fils, ainsi que la valeur de la variable globale "somme" à ce moment-là. Il permet donc de maîtriser le fil d'exécution du père et du fils en vérifiant la valeur de la variable "pid" qui est différente pour les deux: elle vaut 0 pour le fils et le pid du fils pour son père.

3) Il s'affiche à l'écran: "processus fils 'identifiant' : somme = 1" 500 fois, puis "processus pere : somme = 0"; où 'identifiant' varie de 0 à 499

4) On pouvait s'attendre à ce que la somme soit incrémentée de 0 à 500 au final. Ce n'est cependant pas le cas car une fois créé, un processus fils possède sa propre variable somme (puisqu'étant une copie conforme de son père) qu'il incrémente de 1, puis il exécute exit(0) et se termine. Pour chaque processus fils, la variable somme est donc incrémentée de 0 à 1.

5) Le processus père a exécuté la fonction "wait()". Cette fonction permet la synchronisation entre le processus père et tous ses processus fils: elle reçoit un signal émis par le premier processus fils ayant fini de s'exécuter (ce qui la déclenche) et prend en paramètre l'adresse d'une variable dans laquelle est mis le code retour (qui est donc 0 pour tous les processus fils créés) de ce processus fils. Elle met également en pause le processus père (dans ce cas, on dit qu'il "dort") et elle renvoie le pid du processus fils qui l'a déclenché. Elle compare alors ce pid à -1: si celui est différent de -1, le processus père s'éveille et ré-itère le wait qui attend à nouveau le prochain processus fils et ainsi de suite jusqu'au dernier, après quoi le wait renvoie -1 car il n'y a plus de processus fils. Le processus père se réveille alors définitivement et finit à son tour sa propre exécution: c'est pour cela que c’est toujours la ligne du processus père qui s’affiche en dernier.

II - SE SENTIR PLUS LÉGER

1) 2) 3) On crée des thread ici, et non pas des processus fils. De plus, comme les thread ont accès à une variable globale "somme", celle-ci est incrémentée de 0 à 500. Néanmoins, la variable intermédiaire tmp augmente les chances (bien qu'elles soient faibles) d'avoir un résultat différent de 500 car si un premier thread récupère par exemple la valeur 12 dans la variable somme, puis qu'il l'incrémente (et donc elle passe à 13), il se peut qu'avant qu'il mette la nouvelle valeur dans somme, un second thread récupère la valeur dans la variable somme qui correspond à l'ancienne valeur (12) car elle n'a pas eu le temps d'être mise à jour. Ainsi, la somme ne serait incrémentée qu'une fois et pas deux fois successivement. Dans tous les cas, le résultat sera différent de celui du programme précédent.

4) Contrairement aux processus classiques qui sont indépendants les uns des autres car ils disposent chacun d'un environnement qui leur est propre, les thread ont accès à des ressources commune (celle du processus dans lequel ils sont exécutés).

5) A la suite de la condition si, on peut mettre un else { printf("Le pid du processus fils nouvellement créé est %d. \n", pid_fils); } afin de connaître le pid du processus fils qu'on vient de créer. Pour le processus père, on peut remplacer le précédent printf par "printf("Je suis le processus père : somme = %d. De plus, mon pid est %d. \n", somme, getpid());".

6) On constate que les pid sont bien différents les uns des autres.

7) On peut remplacer le précédent printf par "printf("Je suis le thread d'indice %d : somme = %d. De plus, je m'exécute dans le processus de pid %d. \n", i, somme, getpid());" et on constate que tous les thread s'exécutent dans le même processus (main).

8) On constate avec cette commande que chaque processus possède un pid différent.

9) La commande "time" détermine le temps d'exécution d'une certaine commande. Quand la commande est terminée, elle affiche combien de temps elle a mis pour s'exécuter en affichant le temps CPU utilisateur, le temps CPU système et le temps réel.

10) Pour le programme cpt-leger, le temps réel est de 0.299s, le temps utilisateur est de 0.013s et le temps système est de 0.042s.

11) Pour le programme cpt-lourd, le temps réel est de 0.516s, le temps utilisateur est de 0.125s et le temps système est de 0.087s.

12) C'est donc le programme cpt-lourd qui est le plus coûteux en temps pour la machine à faire tourner puisqu'il crée des processus fils qui sont chacun une copie conforme de leur père. Chacun d'entre eux sont donc forcément plus lourds qu'un thread qui est une fonction inclue dans un processus.

III - LES BONS COMPTES FONT LES BONS AMIS 

En passant le nombre de processus créés de 500 à 10 000, on peut constater que la variable somme a beaucoup moins de chance d'être incrémentée jusqu'à 500.

1) Le problème constaté vient du fait que le programme contient une section critique et que l’accès à celle-ci n’est pas protégé. Pour que le programme fonctionne il faut
garantir une exclusion mutuelle. Ceci peut être réalisé grâce au mécanisme des sémaphores qui permet de plus d’éviter une attente active contrairement à d’autres solutions logicielles. 

2) La fonction "pthread_mutex_init(&mutex, NULL)" initialise la structure de données mutex dont l'adresse est passée en paramètre avec les attributs du second paramètre "attr" (lui aussi une structure de données). Si celui-ci vaut NULL (comme c'est le cas ici), par défaut les attributs de mutex sont utilisés. Une fois l'initialisation réussie, l'état de mutex est initialisé et déverrouillé. 

3) Le sémaphore est initialisé à 1 après cette instruction, tel qu'on laisse passer 1 thread à la fois.

4) On peut vouloir donner une valeur supérieure à 1 dans un cas où on voudrait que plusieurs threads exécute en même temps une série d'instructions, comme par exemple pour lire une ressource en même temps.

5) On constate que les threads incrémentent la variable globale somme l'un après l'autre grâce à l'instruction "pthread_mutex_lock(&mutex);" placée avant "int tmp = somme;", puis l'instruction "pthread_mutex_unlock(&mutex);" placée après "somme = tmp;". 

*/