#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>



int main(int argc, char * argv[])
{
  if (argc != 3)
  {
    printf("Le nombre d'arguments est invalide. Utilisation : \n");  
    printf("%s fichier-pour-cle-ipc nbre-de-joueurs_attendus \n", argv[0]);    
    exit(0);
  }
	  
  int cleSem = ftok(argv[1], 'r');
  
  int idSem = semget(cleSem, 1, IPC_CREAT|0600); // 1 : nombre de sémaphores créés

  if(idSem == -1)
  {
    perror("Echec de l'exécution de la fonction semget");
    exit(-1);
  }

  struct sembuf op[1];  // structure pour stocker l'opération sur le sémaphore 0

  op[0].sem_num = 0;  // n° de sémaphore
  op[0].sem_op = -1 * ((short) atoi(argv[2]));    // valeur initiale du sémaphore = - nombre de joueurs saisis
  op[0].sem_flg = 0;  // flag

  semop(idSem, op, 1);

  printf("valeur du sémaphore : %d\n", semctl(idSem, 0, GETVAL)); // 0 est le n° sémaphore
  printf("bloqué\n");
  fflush(stdout);

  return 0;
}

