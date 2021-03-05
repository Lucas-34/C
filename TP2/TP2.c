// TP2 de C

// I ) DEFINITION D'UN TYPE :

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

// En langage C, et par économie de moyens, il n'y a pas de type bool. On travaille en effet avec des entiers en utilisant la convention suivante : la valeur nulle représente la constante booléenne False, et toute autre valeur sera assimilée à la constante True. On peut cependant définir des constantes symboliques comme ceci :

#define false 0
#define true 1

// 1) a)

/* Remarques: - Les 2 catégories de types abstraits existant en langage C sont les énumérations et les struct (type valeur).
              - En langage C, les types abstraits n'ont pas de fonction interne à leur corps. Ces dernières sont définies à l'extérieur et peuvent être utilisées par autre chose que l'instance du type abstrait.      Ainsi, le constructeur n'est pas une procédure ici mais forcément une fonction. On les qualifie néanmoins de "types abstraits" (ou "types complexes") car leur conception reste plus développée que     celle d'un type élémentaire tel que "int".
*/

typedef struct ElementListeEntier ElementListeEntier; // Définition du type des éléments d'une liste d'entiers doublement chaînée.
  
struct ElementListeEntier
{
  int valeur;
  ElementListeEntier* element_precedant; // En langage C, on manipule les adresses/références par le biais des pointeurs. Dans d'autres langages comme en Swift, on les manipule à l'aide de type référence ("class").
  ElementListeEntier* element_suivant;
};

typedef struct ListeEntier ListeEntier; // Définition du type liste d'entiers doublement chaînée. C'est une structure de données qui suit le même principe que celui d'un tableau : la liste est un pointeur vers son premier élément (la tête de la liste) et chaque élément pointe les uns vers les autres.

struct ListeEntier
{
  ElementListeEntier* tete_liste;
};

// b) Remarque: Un "prototype" est une spécification fonctionnelle.

// 2)
ElementListeEntier* constructeurElementListeEntier(int valeur, ElementListeEntier* precedant, ElementListeEntier* suivant)
{
  ElementListeEntier* e;
  
  e = malloc(sizeof(*e));

  e -> valeur = valeur; 
  e -> element_precedant = precedant;
  e -> element_suivant = suivant;

  // Remarque: L'instruction "(*pointeur).attribut = donnée" est équivalente à "pointeur -> attribut = donnée".

  return e;
}

ListeEntier* constructeurListeEntier(int valeur)
{
  ListeEntier* l; // On déclare un pointeur "l" vers une donnée de type ListeEntier ("ListeEntier*" étant le type 'pointeur vers une donnée de type ListeEntier') qui n'a pas de nom explicite mais à laquelle on peut accéder par l'instruction "*l". Par ailleurs, je rappelle qu'on peut accéder à l'adresse d'une donnée x stockée en mémoire par l'instruction "&x".

  l = malloc(sizeof(*l)); // Voir TP1.c pour la définition de la fonction malloc. Par ailleurs, on aurait pu initialiser l en faisant "ListeEntier* l = malloc(sizeof(*l));".

  l -> tete_liste = constructeurElementListeEntier(valeur, NULL, NULL);

  return l;
}

int tailleListe(ListeEntier *l)
{
  ElementListeEntier* element_courant = l -> tete_liste;
  int taille = 0;

  while(element_courant -> element_suivant != NULL)
  {
    element_courant = element_courant -> element_suivant;

    taille++;
  }
}

int estVide(ListeEntier *l)
{
  if(l -> tete_liste == NULL) { return true; }
  else { return false; }
}

ListeEntier* ajoutFin(ListeEntier* l, int valeur)
{
  if(estVide(l) == true) { l -> tete_liste = constructeurElementListeEntier(valeur, NULL, NULL); }
  else
  {
    ElementListeEntier* element_courant = l -> tete_liste; // Je déclare le pointeur "element_courant" et je l'initialise en lui affectant un pointeur vers la tête de la liste. Il pointera de manière générale vers les différents éléments de la liste en partant du premier (la tête de la liste). Il prend donc pour valeurs les pointeurs vers ces éléments.
    
    while(element_courant -> element_suivant != NULL) { element_courant = element_courant -> element_suivant; }

    // On s'est placé sur le dernier élément de la liste.

    ElementListeEntier* nouveau_dernier_element = constructeurElementListeEntier(valeur, element_courant, NULL);

    element_courant -> element_suivant = nouveau_dernier_element;
  }

  return l;
}

ListeEntier* ajoutDebut(ListeEntier* l, int valeur)
{
  if(estVide(l) == true) { l -> tete_liste = constructeurElementListeEntier(valeur, NULL, NULL); }
  else
  {

    ElementListeEntier* nouvelle_tete_liste;

    nouvelle_tete_liste = constructeurElementListeEntier(valeur, NULL, l -> tete_liste);

    l -> tete_liste -> element_precedant = nouvelle_tete_liste;

    l -> tete_liste = nouvelle_tete_liste;
  }

  return l;
}

ElementListeEntier* suivant(ElementListeEntier* e)
{
  return e -> element_suivant;
}

ElementListeEntier* precedant(ElementListeEntier* e)
{
  return e -> element_precedant;
}

ListeEntier* supprimerDebut(ListeEntier* l)
{
  if(estVide(l) == true) { printf("La liste est vide. \n"); }
  else
  {
    l -> tete_liste -> element_suivant -> element_precedant = NULL;
    l -> tete_liste = l -> tete_liste -> element_suivant;

    return l;
  }
}

ListeEntier* supprimerFin(ListeEntier* l)
{
  if(estVide(l) == true) { printf("La liste est vide. \n"); }
  else
  {
    ElementListeEntier* element_courant = l -> tete_liste;
    
    while(element_courant -> element_suivant != NULL) { element_courant = element_courant -> element_suivant; }

    element_courant -> element_precedant -> element_suivant = NULL;
    element_courant -> element_precedant = NULL;

    return l;
  }
}

void printVide(ListeEntier* l)
{
  if(estVide(l) == true) { printf("La liste est vide. \n"); }
  else { printf("La liste n'est pas vide. \n"); }
}

void parcoursListe(ListeEntier* l)
{
  if(estVide(l) == true) { printf("La liste est vide : il n'y a pas de valeur à afficher. \n"); }
  else
  {
    ElementListeEntier* element_courant = l -> tete_liste;
    int indice = 2;
    
    printf("La valeur de la tête de la liste d'entier(s) est %d. \n", element_courant -> valeur);
    
    while(element_courant -> element_suivant != NULL)
    {
      element_courant = element_courant -> element_suivant;
      
      printf("La %de valeur de la liste d'entier(s) est %d. \n", indice, element_courant -> valeur);

      indice ++;
    }

    printf("La valeur du dernier élément de la liste d'entier(s) est %d. \n", element_courant -> valeur);
  } 
}

// 3) Voir programme main en bas.

// II ) POINTEURS DE FONCTION :

// 1)

// Remarque: Jusqu’à maintenant, nous avons manipulé des pointeurs sur des objets, c’est-à-dire des adresses vers des zones mémoires contenant des données (des entiers, des flottants, des structures, etc...). Toutefois, il est également possible de référencer des ensemble d'instructions (programme donc, tel que des fonctions) et ceci est réalisé en C à l’aide des pointeurs de fonction. Ces derniers se définissent à l’aide d’une syntaxe mélangeant celle des pointeurs sur tableau et celles des prototypes de fonction.

ListeEntier* map(ListeEntier* l, int (*pf) (int)) // Dans la syntaxe "int (*pf) (int)", "int" est le type de retour de la fonction, "pf" est le pointeur vers la fonction "(*pf)", et "(int)" est le type du paramètre attendu en entrée.
{
  if(estVide(l) == true) { printf("La liste est vide. \n"); }
  else
  {
    ElementListeEntier* element_courant = l -> tete_liste;
    
    while(element_courant != NULL)
    {
      element_courant -> valeur = pf(element_courant -> valeur); // Remarque: "pf" <=> &'fonction' : c'est le pointeur vers la fonction. En revanche, "pf('paramètre(s)')" <=> 'fonction(paramètre(s))'
      element_courant = element_courant -> element_suivant;
    }
  }
  
  return l;
}

// 2) a)
int doubler(int n)
{
  return 2 * n;
}

// b)
int div2(int n)
{
  return n / 2;
}

// 3) Voir programme main en-dessous.


/* --------------------------------------------------------- */

/* Programme principal permettant de tester mes programmes et structures :

int main()
{
  printf("Je crée la liste d'entier(s) suivante : \n");
  ListeEntier* l = constructeurListeEntier(3);
  printVide(l);
  printf("\n");

  printf("J'ajoute un nouvel élément au début de la liste : \n");
  ajoutDebut(l, 2);
  printVide(l);
  printf("\n");

  printf("J'ajoute encore un nouvel élément au début de la liste : \n");
  ajoutDebut(l, 1);
  printVide(l);
  printf("\n");

  printf("Je supprime la tête de la liste : \n");
  supprimerDebut(l);
  printVide(l);
  printf("\n");

  printf("Je supprime à nouveau la nouvelle tête de la liste : \n");
  supprimerDebut(l);
  printVide(l);
  printf("\n");

  printf("Je remets la liste comme elle était avant ... ");
  ajoutDebut(l, 2);
  printf("et voilà, c'est fait. \n");
  ajoutDebut(l, 1);

  parcoursListe(l);
  printf("\n");
  
  printf("Je multiplie par 2 chaque élément de la liste d'entier(s) : \n");
  map(l, doubler);
  parcoursListe(l);
  printf("\n");
  
  
  printf("Je divise par 2 chaque élément de la liste d'entier(s) : \n");
  map(l, div2);
  parcoursListe(l);
  printf("\n");

  return 0;
}

*/