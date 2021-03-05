#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Les arguments sont invalides. Ils doivent être: '%s fichier_de_référence nombre_de_zones_à_traiter'. \n", argv[0]);

        exit(0);
    }

    int nombre_zones = atoi(argv[2]);

    key_t cle = ftok(argv[1], 'a');

    typedef int* T;

    int idMem = shmget(cle, nombre_zones*sizeof(int), IPC_CREAT | 0666);

    if(idMem == -1)
    {
        perror("Echec de l'exécution de la fonction shmget");

        exit(-1);
    }

    T memoire_partagee = shmat(idMem, NULL, 0);

    int idSem = semget(cle, 1, IPC_CREAT | 0600);

    if(idSem == -1)
    {
        perror("Echec de l'exécution de la fonction semget");

        exit(-1);
    }

    struct sembuf operation[1];

    for(int i=0; i<nombre_zones; i++) // Une boucle permettant de faire les 3 traitements du process 2 (un pour chaque zone à traiter/case du tableau), et avant chaque traitement, le bloquer pendant que le process 1 traite sa tâche.
    {
        printf("Le process 2 est bloqué. \n");

        fflush(stdout);

        // On définit une opération P (associée à la valeur -1) pour que le process courant (process 2) soit bloqué tant que le process 1 n'a pas fini de traiter sa (i+1)e tâche.
        operation[0].sem_num = 0;
        operation[0].sem_op = -1;
        operation[0].sem_flg = 0;

        semop(idSem, operation, 1);

        if(semop(idSem, operation, 1) == -1)
        {
            perror("Echec de l'exécution de la fonction semop");

            exit(-1);
        }

        // Le process courant (process 2) a été débloqué. Il traite sa (i+1)e tâche:
        *(memoire_partagee + i) = *(memoire_partagee + i) * 2;

        sleep(2); // On le fait attendre 2s pour que les traitements soient plus visibles.

        printf("Le %de entier du tableau, après traitement de la %de tâche du process 2, vaut %d. \n", i+1, i+1, *(memoire_partagee + i));

        fflush(stdout);
    }

    shmctl(idMem, 0, IPC_RMID); // On détruit les zones mémoires pour pouvoir les re-créer par la suite et mettre de nouvelles valeurs.

    semctl(idSem, 0, IPC_RMID);

    return 0;
}