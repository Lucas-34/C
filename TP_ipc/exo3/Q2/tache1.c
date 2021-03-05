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

    int nombre_zones = atoi(argv[2]); // Correspond au nombre de zones mémoires à traiter dans la mémoire partagée.

    key_t cle = ftok(argv[1], 'a');

    typedef int* T;

    int idMem = shmget(cle, nombre_zones*sizeof(int), IPC_CREAT | 0666); // On a maintenant 'nombre_zones' zones à traiter (tableau de 'nombre_zones' entiers).

    if(idMem == -1)
    {
        perror("Echec de l'exécution de la fonction shmget");

        exit(-1);
    }

    T memoire_partagee = shmat(idMem, NULL, 0);

    int idSem = semget(cle, 1, IPC_CREAT | 0600); // On a maintenant un tableau de 3 sémaphores (un pour chaque zone à traiter).

    if(idSem == -1)
    {
        perror("Echec de l'exécution de la fonction semget");

        exit(-1);
    }

    struct sembuf operation[1];

    for(int i=0; i<nombre_zones; i++) // Une boucle permettant de faire les 3 traitements du process 1 (un pour chaque zone à traiter/case du tableau), et pour chaque traitement, débloquer le process 2 juste après pour qu'il puisse lui aussi traiter sa tâche.
    {
        *(memoire_partagee + i) = (i+1) * 3; // Le process courant (process 1) traite sa (i+1)e tâche.
        
        sleep(3);

        printf("Le %de entier du tableau, après traitement de la %de tâche du process 1, vaut %d. \n", i+1, i+1, *(memoire_partagee + i));

        fflush(stdout);

        // On définit une opération V (de valeur 1) pour débloquer le process 2 après traitement de la (i+1)e tâche:
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

    // ATTENTION ! Ici, il ne faut pas que le process 1 détruise le sémaphore car, comme il termine ses traitements avant le process 2, il détruirera le sémaphore avant lui tel que ce dernier n'y aura plus accès et sera bloqué avant d'avoir pu traiter toutes ses tâches. Même chose pour les zones mémoires.
    return 0;
}