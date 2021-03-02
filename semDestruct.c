// Description : Le programme dertruit un segment de mémoire partagée s'il existe. Le fichier � prendre en clé est pass� en param�tre du programme.

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

/*

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    printf("Le nombre d'arguments est invalide. Utilisation : \n");
    
    printf("%s fichier-pour-cle-ipc \n", argv[0]);
    
    exit(0);
  }
	  
  int cleSem = ftok(argv[1], 'r');
  
  int idSem = semget(cleSem, 1, IPC_CREAT|0600); // 1 est le nombre de sémaphores créés


  // j'utilise semget de sorte a m'assurer que le tableau a d�truire existe.
  if(idSem == -1)
  {
    perror("Echec de l'exécution de la fonction semget");
    
    exit(-1);
  }

  struct sembuf op[] =
  {
    {0, -1, 0},   // P(-1)
    {0,  5, 0}, // V(1)
  }; 

/*
  op[0].sem_num = 0;
  op[0].sem_op = -1;
  op[0].sem_flg = 0;


  printf("sem id : %d \n", idSem);

  // On doit commencer par initialiser le sémaphore à 1 ici (mutex)
  semop(idSem, &op[1], 1);

  // création d'une zone en mémoire partagée par les process
  // zone de taille d'un long pour y mettre un compteur
  int cleMem = ftok(argv[1], 'r');
  int idMem = shmget(cleMem, sizeof(long), IPC_CREAT|0666);
  
  if(idMem == -1)
  {
    perror("Echec de l'exécution de la fonction shmget");
    
    exit(-1);
  }

  // on récupère un pointeur vers la mémoire partagée
  long* pCompteur = (long*) shmat(idMem, NULL, 0);

  // Début de section critique - lock mutex P(-1)
  semop(idSem, &op[0], 1);

  // opération sur le compteur = section critique (plusieurs processus ne doivent pas la faire en même temps)
  (*pCompteur)++;
  
  // Fin de section critique - unlock mutex V()
  semop(idSem, &op[1], 1);

  printf("La valeur du compteur est %ld. \n", *pCompteur);

  // destruction :
  if(semctl(idSem, 0, IPC_RMID, NULL) == -1) { perror(" erreur semctl : "); }

  return 0;
}

*/