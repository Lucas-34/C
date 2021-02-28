#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h>
#include <sys/wait.h> 

/*
int pid_fils;

int main()
{
  int Pipe[2];
  int Reponse[2];

  int valeur;
  int rep;

  pipe(Pipe);
  pipe(Reponse);

  pid_fils = fork();

  if(pid_fils != 0)
  {
        int moyenne = 0;
        int nb_valeur = 0;
        close(Pipe[1]);
        close(Reponse[1]);
        do
        {      
          read(Pipe[0], &valeur, sizeof(int));
        
          moyenne += valeur;
          nb_valeur ++;

          read(Reponse[0], &rep, sizeof(int));
        }
        while(rep == 1);

        printf("La moyenne des valeurs saisies est %d. \n", moyenne / nb_valeur);
	}
  else if(pid_fils == 0)
  {
        close(Pipe[0]);
        do
        {
            printf("\nVeuillez saisir une valeur entière: ");
            scanf("%d", &valeur);
            write(Pipe[1], &valeur, sizeof(int));
                                                         
            printf("\nVoulez vous effectuer une nouvelle saisie ? Si oui, tapez 'O' sinon tapez 'N': ");
            scanf("%d", &rep);
            write(Reponse[1], &rep, sizeof(int));   

        } while(rep == 1);

        exit(0);
  }

  while(wait(0) != -1) { };

  return EXIT_SUCCESS;
}
*/