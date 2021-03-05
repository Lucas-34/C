#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char* argv[]) // Programme 2 (P2) qui réalise la tâche 2.
{
    if (argc != 2)
    {
        printf("Les arguments sont invalides. Ils doivent être: '%s fichier_de_référence. \n", argv[0]);

        exit(0);
    }

    key_t cle = ftok(argv[1], 'r');

    typedef int* T;

    int idMem = shmget(cle, 1*sizeof(int), IPC_CREAT | 0666);

    if(idMem == -1)
    {
        perror("Echec de l'exécution de la fonction shmget");

        exit(-1);
    }

    T memoire_partagee = shmat(idMem, NULL, 0); // On récupère la même mémoire que dans le process 1 car les paramètres sont les mêmes (mémoire partagée).

    int idSem = semget(cle, 1, IPC_CREAT | 0600);

    if(idSem == -1)
    {
        perror("Echec de l'exécution de la fonction semget");

        exit(-1);
    }

    struct sembuf operation[1];

    printf("Le compteur avant le blocage du process 2 vaut %d. \n", semctl(idSem, 0, GETVAL));

    fflush(stdout);

    printf("Le process 2 est bloqué. \n");

    fflush(stdout);

    // On définit une opération P (associée à la valeur -1) pour que le process courant (process 2) soit bloqué tant que le process 1 n'a pas fini de traiter sa tâche.
    operation[0].sem_num = 0;
    operation[0].sem_op = -1;
    operation[0].sem_flg = 0;

    if(semop(idSem, operation, 1) == -1)
    {
        perror("Echec de l'exécution de la fonction semop");

        exit(-1);
    }

    // Le process 2 est débloqué car le process 1 a fini de traiter sa tâche. Par une opération V (de valeur 1), il a alors incrémenté le compteur de 0 à 1 tel que le nombre de places demandées = nombre de places disponibles et le process 2 peut entrer dans la section critique.
    printf("Le compteur après le déblocage du process 2 vaut %d. \n", semctl(idSem, 0, GETVAL));

    fflush(stdout);

    *memoire_partagee = *memoire_partagee * 2; // Le process courant (process 2) traite sa tâche.

    printf("L'unique entier du tableau, après traitement de la tâche 2, vaut %d. \n", *memoire_partagee);

    fflush(stdout);

    semctl(idSem, 0, IPC_RMID);

    return 0;
}