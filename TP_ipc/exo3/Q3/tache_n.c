#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char* argv[]) // Programme n
{
    if(argc != 5)
    {
        printf("Les arguments sont invalides. Ils doivent être: '%s fichier_de_référence indice_process nombre_de_zones_à_traiter nombre_de_processus'. \n", argv[0]); // Les indices des process (n) commencent à 0.

        exit(0);
    }

    int indice_process = atoi(argv[2]);

    int nombre_zones = atoi(argv[3]);

    int nombre_semaphores = atoi(argv[4])-1; // Il faut 1 sémaphore pour chaque processus d'indice différent de 0 (celui-ci n'étant pas bloqué). Un sémaphore est ré-utilisé pour toutes les tâches d'un processus.

    key_t cle = ftok(argv[1], 'a');

    typedef int* T;

    int idMem = shmget(cle, nombre_zones*sizeof(int), IPC_CREAT | 0666);

    if(idMem == -1)
    {
        perror("Echec de l'exécution de la fonction shmget");

        exit(-1);
    }

    T memoire_partagee = shmat(idMem, NULL, 0);

    int idSem = semget(cle, nombre_semaphores, IPC_CREAT | 0600);

    if(idSem == -1)
    {
        perror("Echec de l'exécution de la fonction semget");

        exit(-1);
    }

    struct sembuf operation[1];

    if(indice_process == 0) // Processus n=0
    {
        for(int i=0; i<nombre_zones; i++)
        {
            *(memoire_partagee + i) = (i+1) * 3; // Le process 0 traite sa (i+1)e tâche.
            
            sleep(3);

            printf("Le %de entier du tableau, après traitement de la %de tâche du process %d, vaut %d. \n", i+1, i+1, indice_process, *(memoire_partagee + i));

            fflush(stdout);

            // On définit une opération V (de valeur 1) pour débloquer le process (n+1) après traitement de la (i+1)e tâche:
            operation[0].sem_num = 0;
            operation[0].sem_op = 1;
            operation[0].sem_flg = 0;

            semop(idSem, operation, 1);

            if(semop(idSem, operation, 1) == -1)
            {
                perror("Echec de l'exécution de la fonction semop");

                exit(-1);
            }
        }
    }
    else if(indice_process != nombre_semaphores)
    {
        for(int i=0; i<nombre_zones; i++)
        {
            printf("Le process %d est bloqué. \n", indice_process);

            fflush(stdout);

            // On définit une opération P (associée à la valeur -1) pour que le process courant soit bloqué tant que le process précédent n'a pas fini de traiter sa (i+1)e tâche.
            operation[0].sem_num = indice_process-1; // Chaque processus d'indice 'indice_process' est associé à un sémaphore d'indice 'indice_process'-1.
            operation[0].sem_op = -1;
            operation[0].sem_flg = 0;

            semop(idSem, operation, 1);

            if(semop(idSem, operation, 1) == -1)
            {
                perror("Echec de l'exécution de la fonction semop");

                exit(-1);
            }

            // Le process courant a été débloqué. Il traite sa (i+1)e tâche:
            *(memoire_partagee + i) = *(memoire_partagee + i) * indice_process;

            sleep(2);

            printf("Le %de entier du tableau, après traitement de la %de tâche du process %d, vaut %d. \n", i+1, i+1, indice_process, *(memoire_partagee + i));

            fflush(stdout);

            // On définit une opération V (associée à la valeur 1) pour que le process suivant soit débloqué:
            operation[0].sem_num = indice_process;
            operation[0].sem_op = 1;
            operation[0].sem_flg = 0;

            semop(idSem, operation, 1);

            if(semop(idSem, operation, 1) == -1)
            {
                perror("Echec de l'exécution de la fonction semop");

                exit(-1);
            }
        }
    }
    else // Dernier processus
    {
        for(int i=0; i<nombre_zones; i++)
        {
            printf("Le process dernier est bloqué. \n");

            fflush(stdout);

            operation[0].sem_num = indice_process-1;
            operation[0].sem_op = -1;
            operation[0].sem_flg = 0;

            semop(idSem, operation, 1);

            if(semop(idSem, operation, 1) == -1)
            {
                perror("Echec de l'exécution de la fonction semop");

                exit(-1);
            }

            // Le dernier process a été débloqué. Il traite sa (i+1)e tâche:
            *(memoire_partagee + i) = *(memoire_partagee + i) * indice_process;

            sleep(2);

            printf("Le %de entier du tableau, après traitement de la %de tâche du dernier process, vaut %d. \n", i+1, i+1, *(memoire_partagee + i));

            fflush(stdout);
        }

        shmctl(idMem, 0, IPC_RMID);

        semctl(idSem, 0, IPC_RMID);
    }

    return 0;
}