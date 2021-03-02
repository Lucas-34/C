/*
  Description : 
  Le programme cr�e un segment de m�moire partag� dont le contenu est un tableau d'entiers et initialise ce tableau � 0. Le nombre d'�lements du tableau et le fichier � prendre en cl� sont pass�s en param�tre du programme.
  
*/

/*

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>


int main(int argc, char * argv[]){

  if (argc!=3) {
    printf("Nbre d'args invalide, utilisation :\n");;
    printf("%s nombre-elements fichier-pour-cle-ipc\n", argv[0]);
    exit(0);
  }
	  
  int clemem=ftok(argv[2], 'r');

  int laMem;

  if ((laMem=shmget(clemem, atoi(argv[1])*sizeof(int), IPC_CREAT | IPC_EXCL | 0600))==-1){
    perror("erreur shmget : ");
    exit(-1);
  }

  printf("mem id : %d \n", laMem);

	  
  //attachement au segment pour pouvoir y acc�der
  int * p_att = (int *)shmat(laMem, NULL, 0);
  if (p_att== (int *)-1){
    perror("erreur shmat : ");
    exit(-1);
  }

  // j'ai un pointeur sur le segment, j'initialise le tableau 
	 
  for(int i=0; i < atoi(argv[1]); i++){
    p_att[i] = 0;
  }

  // d�tachement pour signaler au syst�me la fin de l'utilisation du segment

  if (shmdt(p_att) == -1){
    perror("erreur shmdt : ");
    exit(-1);
  }
	  
  return 0;
}

*/
