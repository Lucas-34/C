/*
  Description : 
  Le programme dertruit un segment de mémoire partagé s'il existe. Le fichier à prendre en clé est passé en paramètre du programme.
  
*/


#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

int main(int argc, char * argv[]){

  if (argc!=2) {
    printf("Nbre d'args invalide, utilisation :\n");;
    printf("%s fichier-pour-cle-ipc\n", argv[0]);
    exit(0);
  }
	  
  int cleSem=ftok(argv[1], 'r');

  int idSem = semget(cleSem, 1, 0600);

  // j'utilise semget de sorte a m'assurer que le tableau a détruire existe.
  if (idSem==-1){
    perror("erreur  semget");
    exit(-1);
  }

  printf("sem id : %d \n", idSem);

  // destruction :
  if (semctl(idSem, 0, IPC_RMID, NULL)==-1)
    perror(" erreur semctl : ");

  return 0;
}

