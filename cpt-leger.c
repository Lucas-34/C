#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h> 
#define NB_THREADS 500

int somme = 0;

/*

void* Fils(void *t) // Remarque: "void* est le type 'pointeur vers une donnée de type non-défini"
{
  int i = (long) t; // Remarque: t est un pointeur mais "(cast) t" <=> "(cast) *t"
    
  int tmp = somme;
 
  tmp++;

  somme = tmp;
 
  // Remarque: Comme les thread créés successivement s'exécutent plus ou moins en parallèle, utiliser une variable intermédiaire "tmp" fait que si un premier thread récupère par exemple la valeur 12 dans la variable somme, puis qu'il l'incrémente (et donc elle passe à 13), il se peut qu'avant qu'il mette la nouvelle valeur dans somme, un second thread récupère la valeur dans la variable somme qui correspond à l'ancienne valeur (12) car elle n'a pas eu le temps d'être mise à jour. Ainsi, la somme ne serait incrémentée qu'une fois et pas deux fois successivement. Le résultat a donc des chances (bien qu'elles soient faibles) d'être différent de 500 au final.

  printf("Je suis le thread d'indice %d : somme = %d. De plus, je m'exécute dans le processus de pid %d. \n", i, somme, getpid()); // La fonction "getpid()" renvoie le pid du processus courant. Ainsi, comme le thread dans lequel on exécute cette fonction se trouve lui-même dans le processus (main), getpid() renvoie le pid de ce processus.
  
  pthread_exit(0); // Même chose que exit pour un processus, mais pour un thread (sous-processus).
}

int main()
{
  long i;
  
  pthread_t thread[NB_THREADS]; // "pthread_t" est le type 'identifiant d'un thread', en l'occurrence un entier long. Dans le tableau "thread[NB_THREADS]" on mettra les identifiants des 500 thread (indicés de 0 à 499) qu'on va créer.
  
  for(i=0; i < NB_THREADS; i++) { pthread_create(&thread[i], NULL, Fils, (void*) i); } 
  
   Remarques: - "Fils" est le pointeur vers la fonction Fils() (Fils <=> &Fils()).
                - "&thread[i]" est l'adresse de l'élément d'indice i du tableau dans lequel on mettra l'identifiant du thread nouvellement créé.
                - "pthread_create()" est la fonction qui "crée un thread": plus précisément, elle convertit une fonction dont l'adresse est passée en paramètre en un thread.
                - "(void*) i" est un pointeur vers une donnée de type void. *i sera alors la donnée que la fonction Fils() prendra en paramètre.
  

  for(i=0; i < NB_THREADS; i++) { pthread_join(thread[i], NULL); } // "pthread_join()" est la fonction qui attend que le thread dont l'identifiant est passé en paramètre se termine (exécute "pthread_exit(0)"). Cependant ici, il les prend dans l'ordre contrairement au wait() qui prenait le premier qui se terminait.
  
  printf("Je suis le processus : somme = %d. De plus, mon pid est %d. \n", somme, getpid()); // Comme les thread ont accès à une variable globale "somme", celle-ci est incrémentée de 0 à 500. Néanmoins, la variable intermédiaire tmp augmente les chances (bien qu'elles soient faibles) d'avoir un résultat différent de 500.
  
  return 0;
}

 Remarques: - Une "section critique" est une série d'instructions qui ne doit être exécutée que par un seul thread à la fois (c'est par exemple ce qu'on a des lignes 13 à 17). Pour pallier ce problème, on                   utilise un "sémaphore" (aussi appelé "mutex" en anglais), c'est-à-dire un verrou permettant aux threads de passer l'un derrière l'autre (on parle d'une "exclusion mutuelle"). Cela permet                       également aux threads qui attendent leur tour d'attendre passivement car ils sont effectivement mis en pause tant que ce n'est pas à eux de passer. Le principe est qu'on utilise une fonction                   "pthread_mutex_lock(&mutex)" qui laisse passer le premier thread exécutant cette fonction et bloque les autres en attendant que le premier ait fini d'exécuter sa série d'instructions, puis une                 fois que c'est fait, on appelle une fonction "pthread_mutex_unlock(&mutex)" qui débloque le suivant et ainsi de suite jusqu'au dernier.
              - La valeur du mutex correspond au nombre de threads qu'on autorise à passer en même temps. Par défaut, on l'initialise à 1.
*/