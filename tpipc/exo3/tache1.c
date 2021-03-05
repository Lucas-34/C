#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>

int main(int argc, char* argv[]) // Programme 1 (P1) qui réalise la tâche 1.
{
    if (argc != 2)
    {
        printf("Les arguments sont invalides. Ils doivent être: '%s fichier_de_référence. \n", argv[0]);

        exit(0);
    }

    key_t cle = ftok(argv[1], 'r'); // On crée une clé qui sera utilisée par le tableau de sémaphores et par la mémoire partagée.

    typedef int* T; // "T" est le type 'pointeur vers un entier' (T <=> int*).

    int idMem = shmget(cle, 1*sizeof(int), IPC_CREAT | 0666); // On passe en paramètre la taille d'un tableau d'1 entier. Comme ce tableau est l'unique donnée dans la mémoire partagée, il y a une correspondance entre les deux: la mémoire partagée est allouée à cet entier.

    if (idMem == -1)
    {
        perror("Echec de l'exécution de la fonction shmget.");

        exit(-1);
    }

    T memoire_partagee = shmat(idMem, NULL, 0); // "memoire_partagee" est un pointeur contenant l'adresse de la mémoire partagée (soit l'adresse de l'unique entier du tableau qui est alloué à cette mémoire). Grâce à cette variable, le process courant a accès au contenu de la mémoire partagée (l'entier unique du tableau).

    int idSem = semget(cle, 1, IPC_CREAT | 0600);

    if (idSem == -1)
    {
        perror("Echec de l'exécution de la fonction semget.");

        exit(-1);
    }

    struct sembuf operation[1];

    *memoire_partagee = 5; // Le process courant (process 1) traite sa tâche.

    printf("L'unique entier du tableau, après traitement de la tâche 1, vaut %d. \n", *memoire_partagee);

    fflush(stdout);

    // On définit une opération V (de valeur 1) pour débloquer le process 2:
    operation[0].sem_num = 0;
    operation[0].sem_op = 1;
    operation[0].sem_flg = 0;

    semop(idSem, operation, 1);

    if (semop(idSem, operation, 1) == -1)
    {
        perror("Echec de l'exécution de la fonction semop.");

        exit(-1);
    }

    printf("Le compteur après le déblocage du process 2 vaut %d. \n", semctl(idSem, 0, GETVAL));

    fflush(stdout);

    semctl(idSem, 0, IPC_RMID); // On détruit le sémaphore car il ne nous sert plus.

    return 0;
}