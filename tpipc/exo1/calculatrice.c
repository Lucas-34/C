#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>



int main(int argc, char* argv[]) // Correspond à notre programme calculatrice
{
  if(argc != 2)
  {
    printf("Erreur, il faut ces arguments pour exécuter la ligne de commande: ./calculatrice chemin_fichier_clé. \n");
    
    exit(1);
  }
  
  printf("L'exécution de la ligne de commande s'est bien passée. \n");

  key_t cle = ftok(argv[1], 'z'); // On crée à nouveau la clé de la file de messages, identique à celle créée dans le processus client car on utilise les mêmes arguments caractéristiques (le nom du fichier et le caractère).

  if(cle == -1)
  {
    perror("Echec de l'exécution de la fonction ftok. \n");

    exit(1);
  }
  else { printf("L'exécution de la fonction ftok s'est bien passée. \n"); }
  
  int id_file_msg = msgget(cle, IPC_CREAT | 0666); // On crée à nouveau l'identifiant de la file de messages, identique à celui créé dans le processus client car on utilise la même clé.

  if(id_file_msg == -1)
  {
    perror("Echec de l'exécution de la fonction msgget. \n");

    exit(1);
  }
  else { printf("L'exécution de la fonction msgget s'est bien passée. \n"); }

  typedef struct requete requete;

  struct requete
  {
    long etiquette_requete;
    
    struct contenu
    {
      int id_operateur;
      int operande1;
      int operande2; 
    } Contenu;
  } Requete;
  
  // Réception du message issu de la file de messages:
  
  if(msgrcv(id_file_msg, (void*) &Requete, sizeof(Requete.Contenu), 1, 0) == -1)
  {
    perror("Echec de l'exécution de la fonction msgrcv. \n");

    exit(1);
  }

  int Resultat;

  switch(Requete.Contenu.id_operateur) // L'opérateur "switch(x)" permet de passer d'un cas à un autre (définis dans son corps) selon la valeur du paramètre 'x'. Chaque cas correspond à une des valeurs pouvant être prise par ce paramètre.
    {
      case 1:
        Resultat = Requete.Contenu.operande1 + Requete.Contenu.operande2; // Instruction réalisée dans ce cas.
        break; // Par défaut, on passe par les différents cas sans interruption. Il faut donc mettre un break pour mettre fin à l'éxecution d'un cas.
      
      case 2:
        Resultat = Requete.Contenu.operande1 - Requete.Contenu.operande2;
        break;
      
      case 3:
        Resultat = Requete.Contenu.operande1 * Requete.Contenu.operande2;
        break;
      
      case 4:
        Resultat = Requete.Contenu.operande1 / Requete.Contenu.operande2;
        break;
    }

  // On renvoie maintenant le résultat dans la file de messages pour que le processus client puisse le récupérer. On a donc besoin d'un autre type de message pour ça:

  typedef struct reponse reponse;

  struct reponse
  {
    long etiquette_reponse;

    int resultat;
  } Reponse;

  // On initialise la réponse:

  Reponse.etiquette_reponse = 2;
  Reponse.resultat = Resultat;

  // On l'envoie:

  if(msgsnd(id_file_msg, (void*) &Reponse, sizeof(Reponse.resultat), 0) == -1)
  {
    perror("Echec de l'exécution de la fonction msgsnd. \n");

    exit(1);
  }

  printf("L'exécution de la fonction msgsnd s'est bien passée. \n");

  return 0;
}

