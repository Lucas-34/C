#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    printf("initJeu : Les arguments sont invalides. Ils doivent être: '%s fichier_de_référence nombre_de_joueurs_attendus'. \n", argv[0]);
    
    exit(0);
  }

  key_t cle = ftok(argv[1], 'r'); // On crée la clé.

  int idSem = semget(cle, 1, IPC_CREAT | 0600); // Le 2nd paramètre correspond au nombre de sémaphores présents dans notre tableau de sémaphores. Il y a donc ici 1 sémaphore.

  if (idSem == -1)
  {
    perror("initJeu : Echec de l'exécution de la fonction semget");
    exit(-1);
  }

  struct sembuf operation[1]; // "sembuf" est le type 'opération sur un sémaphore'. Un sémaphore est une structure de données qui comprend notamment comme attribut un compteur (entier) correspondant au nombre de process pouvant passer en même temps dans la section critique. Une opération sur un sémaphore est plus précisément une opération sur son compteur: il s'agit d'incrémenter ou de décrémenter le compteur. On définit par ailleurs 3 catégories d'opérations: V pour l'incrémentation (valeur positive), P pour la décrémentation (valeur négative), et Z qui est un peu spéciale car elle correspond à la valeur 0 (donc le compteur ne change pas) mais fait aussi que chaque process qui exécutera cette opération sera bloqué du moment que le compteur est différent de 0. Ici, "operation" est un tableau d'1 opération.

  // On initialise l'unique opération:
  operation[0].sem_num = 0; // Les numéros des sémaphores ne correspondent pas à leur indice dans le tableau de sémaphores. Ces numéros commencent à 0.
  operation[0].sem_op = (short) atoi(argv[2]); // Initialement, le compteur d'un sémaphore vaut 0. On va donc lui ajouter ( nombre_de_joueurs_attendus) (valeur affectée à sem_op qui correspond à la valeur qui est ajoutée au compteur). Ainsi, à chaque fois qu'un process arrivera sur la section critique, on incrémentera le compteur de 1 (opération V avec un sem_op = 1) et on les bloquera (opération Z) tel que lorsque le compteur aura atteint 0, cela voudra dire que tous les process auront été réunis au même endroit (là on exécute ces 2 opérations).
  operation[0].sem_flg = 0; // Option de l'opération

  semop(idSem, operation, 1); // La fonction "semop" permet d'exécuter l'opération dont la syntaxe avait été définie précédemment. Dans le cas où sem_op est négatif, semop bloque les process qui l'exécuteront. Dans le cas où sem_op est nul, semop bloque les process qui l'exécutent tant que le compteur est différent de 0.

  printf("initJeu : La valeur du compteur à ce moment est %d. \n", semctl(idSem, 0, GETVAL)); // Le 2nd paramètre est le numéro du sémaphore. Il n'y en a qu'1 ici, de numéro 0.
  fflush(stdout); // Permet de forcer l'écriture sur la sortie standard.


 // On définit une opération Z pour bloquer le process jusqu'à ce que le compteur soit à 0:
  operation[0].sem_num = 0;
  operation[0].sem_op = 0;
  operation[0].sem_flg = 0;
  semop(idSem, operation, 1);

  printf("initJeu : débloqué aussi !");
  fflush(stdout);

  return 0;
}