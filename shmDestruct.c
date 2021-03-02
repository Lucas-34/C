/*
  Description : 
  Le programme dertruit un segment de m�moire partag� s'il existe. Le fichier � prendre en cl� est pass� en param�tre du programme.
  
*/

/*

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char * argv[]){

  if (argc!=2) {
    printf("Nbre d'args invalide, utilisation :\n");;
    printf("%s fichier-pour-cle-ipc\n", argv[0]);
    exit(0);
  }
	  
  int clemem=ftok(argv[1], 'r');

  int laMem;

  // j'utilise shmget de sorte a m'assurer que le segment a d�truire existe.
  if ((laMem=shmget(clemem, 1, 0600))==-1){
    perror("erreur shmget : ");
    exit(-1);
  }

  printf("mem id : %d \n", laMem);

  // destruction :
  if (shmctl(laMem, IPC_RMID, NULL)==-1)
    perror("erreur shmctl : ");

  return 0;
}

*/