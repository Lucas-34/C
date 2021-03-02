#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>

// On veut mettre en place une application composée de 2 programmes: le premier, appelé "client", génère et envoie des requêtes au second, appelé "calculatrice". La calculatrice résout les requêtes (en l'occurrence, des opérations algébriques) et renvoie les réponses au client. Les requêtes sont des opérations mathématiques simples à exécuter (par exemple: 7 ∗ 5). Les deux programmes vont donc avoir besoin de communiquer entre eux, et pour ça on va utiliser une file de messages: C'est une structure de données permettant la communication de données/informations (aussi appelées "messages") entre plusieurs processus. Un message est lui aussi une structure de données, et il possède une étiquette permettant de l'identifier.

/* Le type d'un message est "msgbuf". Il s'agit d'une structure contenant son étiquette comme premier attribut, suivie de données correspondant à l'information transmise par le message. Ces dernières ne doivent pas contenir de pointeurs. Exemple:

typedef struct msgbuf msgbuf;

struct msgbuf
{
  long etiquette; 
  int num[10];
  char texte[30];  
};

*/



int main(int argc, char* argv[]) // Correspond à notre programme client.
{
  if(argc != 5) // On a besoin de 5 arguments sur la ligne de commande.
  {
    printf("Erreur, il faut ces arguments pour exécuter la ligne de commande: ./client opérande1 opérateur opérande2 chemin_fichier_clé. \n");
    
    exit(1);
  }
  
  printf("L'exécution de la ligne de commande s'est bien passée. \n");

  key_t cle = ftok(argv[4], 'z'); // La fonction "key_t ftok(const char* nom_chemin, int n)" renvoie la clé (de type "key_t") d'une file de messages à partir du chemin d'un fichier existant, et d'un entier quelconque (qui peut d'ailleurs être un caractère pour certains systèmes, comme c'est le cas ici). En fait, la clé créée sera composée de ces 2 éléments. De plus, une clé est différente d'une file de messages à l'autre.
  
  if(cle == -1) // Si la "cle" vaut -1, c'est qu'il y a eu un problème.
  {
    perror("Echec de l'exécution de la fonction ftok. \n");  // La fonction "perror('chaîne_de_caractères')" permet d'afficher un message d'erreur.

    exit(1);
  }
  else { printf("L'exécution de la fonction ftok s'est bien passée. \n"); }
  
  int id_file_msg = msgget(cle, IPC_CREAT | 0666); // La fonction "int msgget(key_t cle, int droits)" permet de calculer l'identifiant (un entier) d'une certaine file de messages à partir de sa 'cle' et d'au moins 1 droit d'accès identifié par un entier (présenté explicitement ou sous la forme d'une constante symbolique telle que "IPC_CREAT" ou "O_RDONLY"). Dans notre cas, 0666 représente le droit d'accès en écriture à la file de messages.

  if(id_file_msg == -1)
  {
    perror("Echec de l'exécution de la fonction msgget. \n");

    exit(1);
  }
  else { printf("L'exécution de la fonction msgget s'est bien passée. \n"); }

  typedef struct requete requete;

  struct requete // Structure des requêtes (messages)
  {
    long etiquette_requete;

    struct contenu // Il s'agit de l'opération. Pour accéder à ce type, il faut faire "requete.contenu".
    {
      int id_operateur;  // 1: +, 2 : -, 3: *, 4: /
      int operande1;
      int operande2; 
    } Contenu; // On déclare une instance "Contenu" du type "contenu". Il s'agira donc d'un de nos 2 attributs.
  } Requete; // Même chose pour le type "requete".

  // On initialise le message avec les arguments de la ligne de commande, avant de l'envoyer à la calculatrice:

  Requete.etiquette_requete = 1;
  Requete.Contenu.operande1 = atoi(argv[1]); // La fonction "atoi(x)" permet de convertir la valeur passée en paramètre en entier.
  Requete.Contenu.id_operateur = atoi(argv[2]);
  Requete.Contenu.operande2 = atoi(argv[3]);
  
  // Envoie du message dans la file de messages. Il sera ensuite récupéré par la calculatrice:
  
  if(msgsnd(id_file_msg, (void*) &Requete, sizeof(Requete.Contenu), 0) == -1)
  {
    perror("Echec de l'exécution de la fonction msgsnd. \n");

    exit(1);
  }

  printf("L'exécution de la fonction msgsnd s'est bien passée. \n");

  typedef struct reponse reponse;

  struct reponse
  {
    long etiquette_reponse;

    int resultat;
  } Reponse;

  // Réception de la réponse issue de la file de messages:
  
  if(msgrcv(id_file_msg, (void*) &Reponse, sizeof(Reponse.resultat), 2, 0) == -1)
  {
    perror("Echec de l'exécution de la fonction msgrcv. \n");

    exit(1);
  }

  printf("Le résultat de l'opération est %d. \n", Reponse.resultat);

  return 0;
}

