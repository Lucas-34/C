#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    printf("Joueur: Les arguments sont invalides. Ils doivent être: '%s fichier_de_référence. \n", argv[0]);
    
    exit(0);
  }

  key_t cle = ftok(argv[1], 'r'); // On re-crée la même clé que dans le programme initJeu car les paramètres sont identiques.

  int idSem = semget(cle, 1, IPC_CREAT | 0600); // On re-crée le même identifiant. Comme on a accès au même objet IPC, on aura accès au même sémaphore de numéro 0.

  if(idSem == -1)
  {
    perror("Joueur: Echec de l'exécution de la fonction semget."); 
    
    exit(-1);
  }

  struct sembuf operation[1];

  // On définit une opération P (associée à la valeur -1):
  operation[0].sem_num = 0;
  operation[0].sem_op = -1; // A l'endroit où les process (joueurs) doivent se réunir, chacun d'entre eux décrémentera le compteur du sémaphore de 1 et entrera dans la section critique ssi |-1| = 1 <= nombre_de_joueurs_attendus, sinon sera bloqué et le compteur reste inchangé.
  operation[0].sem_flg = 0;
  
  semop(idSem, operation, 1);
  
  if(semop(idSem, operation, 1) == -1)
  {
    perror("Joueur: Echec de l'exécution de la fonction semop.");
    
    exit(-1);
  }

  printf("Joueur: Le compteur du sémaphore avant le blocage du process courant est %d. \n", semctl(idSem, 0, GETVAL));
  
  fflush(stdout);
  
  printf("Joueur: Le process courant est bloqué. \n");
  
  fflush(stdout);

  // On définit une opération Z pour bloquer les process jusqu'à ce que le compteur soit à 0:
  operation[0].sem_num = 0;
  operation[0].sem_op = 0;
  operation[0].sem_flg = 0;
  
  semop(idSem, operation, 1);

  if(semop(idSem, operation, 1) == -1)
  {
    perror("Joueur: Echec de l'exécution de la fonction semop.");
    
    exit(-1);
  }

  printf("Joueur: Le compteur a atteint 0. Tous les process sont débloqués ! \n");
  
  fflush(stdout);
  
  printf("Joueur: Le compteur après le déblocage des process vaut %d. \n", semctl(idSem, 0, GETVAL));
  
  fflush(stdout);

  return 0;
}