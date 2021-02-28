#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h>
#include <sys/wait.h> 

int pid_fils;
/*
int main() // Processus père
{
  int Descripteur[2]; // Tableau de 2 entiers, l'un (contenu dans Descripteur[1]) identifiant une zone mémoire où l'on écrira notre message, l'autre (contenu dans Descripteur[0]) identifiant une autre zone mémoire où l'on lira le message. On l'appelle donc "Descripteur" car il contient les identifiants/descripteurs de ces deux zones mémoire correspondant symboliquement à l'entrée et la sortie du tube.

  char message[256]; // Valeur que l'on transfert via un tube du processus père au processus fils. Il s'agit d'un tableau de 256 caractères. Rappel: Un tableau 't' est un pointeur vers son 1er élément.

  pipe(Descripteur); // Fonction qui crée la variable 'Descripteur'. Elle retourne 0 en cas de succès, -1 en cas d’échec. Descripteur[0] est alors créé en lecture et Descripteur[1] est créé en écriture.

  pid_fils = fork(); // On crée le processus fils.

  if(pid_fils != 0) // On se trouve dans le processus père.
  { 
    printf("Je suis le processus père et je vais envoyer un message à mon fils. \n");

    close(Descripteur[0]); // Par défaut, les 2 éléments (l'un correspondant à la lecture, l'autre à l'écriture) du tube sont "ouverts". Cependant, les actions de lecture et d'écriture sont complémentaires et on ne peut alors réaliser que l'une des deux à la fois. Il faut ainsi en fermer une quand on veut utiliser l'autre.

    sprintf(message, "Bonjour mon fils, c'est ton père."); // La fonction "sprintf(char tableau_de_caractères[n], 'message')" permet d'affecter la valeur 'message' au tableau de caractères.

    write(Descripteur[1], message, 256); // La fonction "int write(Descripteur[1], T* pvaleur, int longueur)" permet d'écrire dans le 2nd élément du tube ("Descripteur[1]") la valeur de type T dont on passe le pointeur ("T* pvaleur") en paramètre, valeur dont la taille (nombre de données élémentaires la constituant) est "longueur". Pour une chaîne de caractères (ou tableau de caractères), on passe la longueur de la chaîne (soit la taille de ce tableau). Pour un entier, on passe 1 en paramètre. Si l'on utilise Descripteur[0] et non Descripteur[1] le programme plante.
	}
  else if(pid_fils == 0) // On se trouve dans le processus fils.
  {
    close(Descripteur[1]);

    read(Descripteur[0], message, 256); // On lit le message situé dans Descripteur[0] et on le met dans la variable "message" propre au processus fils, celui-ci en disposant puisqu'il est une copie conforme de son père.

    printf("\n");
    
    printf("Je suis le processus fils et je viens de recevoir un message de mon père qui est: '%s' \n", message);

    exit(0); // Le processus fils se termine.
  }

  while(wait(0) != -1) { };

  return EXIT_SUCCESS;
}
*/