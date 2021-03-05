#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h> 
#define _POSIX_SOURCE 1

/*

int NB_THREADS = 10;
int somme = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // On initialise la donnée mutex.

void* Fils(void *t) // Fonction qui sera convertie en thread.
{
  srand(time(NULL) ^ (getpid() << 16));
  
  int i = (long) t; 

  pthread_mutex_lock(&mutex); // On laisse passer le premier thread exécutant cette fonction et on bloque les autres.

  int tmp = somme;
  
  tmp ++;
  
  int randomTime;

  randomTime = rand() % 3; // Remarque: La fonction "rand()" génère un entier aléatoire qui correspondra ici au temps d'attente du thread.
  
  sleep(randomTime); // Remarque: La fonction "sleep(x)" met en pause pendant x secondes le thread courant.
  
  somme = tmp;
  
  pthread_mutex_unlock(&mutex); // Le premier thread à être passé a fini d'exécuter sa série d'instructions. On débloque alors les threads en attente et on laisse passer le suivant.

  printf("Je suis le processus fils d'indice %d : somme = %d. \n", i, somme);
  
  pthread_exit(0); // Le thread courant se termine.
}

int main(int argc, char** argv) // "char** argv" est un pointeur vers un pointeur d'un caractère.
{
  pthread_t tid; // Variable prenant pour valeurs les identifiants des threads.
  pthread_t Threads_id[NB_THREADS]; // Tableau dans lequel on stocke les identifiants des 10 threads créés, identifiants dont le type est "pthread_t".
  int i;
  
  printf("Je suis le processus père : somme = %d. \n", somme);

  for(i=0; i < NB_THREADS; i++)
  {
    if(pthread_create(&tid, NULL, Fils, NULL) != 0)
    {
      printf("Un nouveau thread vient d'être créé. \n");
      
      exit(1);
    }
 	  else { Threads_id[i] = tid; }
  }

	for(i=0; i < NB_THREADS; i++) { pthread_join(Threads_id[i], NULL); }
  
  printf("Je suis le processus père : somme = %d. \n", somme);
       
  return EXIT_SUCCESS;
}

*/