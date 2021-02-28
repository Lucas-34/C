// TP1 de C

// II ) EXERCICES SIMPLES :

#include <stdlib.h>
#include <limits.h> // Cette bibliothèque permet de définir la valeur des 8 premières constantes symboliques.
#include <stdio.h> // Cette bibliothèque permet de définir la valeur de "EOF" ("End Of File", un caractère marquant la fin du fichier.)
#include <string.h> // Cette bibliothèque me permet d'utiliser la fonction "strlen" qui renvoie la taille d'une chaîne de caractères.
#define TAILLE_MAX 1000 // Définit la valeur de la constante symbolique "TAILLE_MAX" en lui affectant la valeur 1000.

// Ce que j'inclue au-dessus sont des bibliothèques C. "include" est l'équivalent du "import" dans d'autres langages.

// 1)
void affichage_constantes_symboliques()
{
  printf("Les valeurs des constantes symboliques sont respectivement : %d, %d, %d, %d, %ld, %d, %d, %ld, %c \n", CHAR_MIN, CHAR_MAX, INT_MIN, SHRT_MIN, LONG_MIN, INT_MAX, SHRT_MAX, LONG_MAX, EOF);
}

// 2)
void evaluation_contenu_fichier(char nom_fichier[]) // On crée une chaîne de caractères comme étant un tableau de caractères car string n'existe pas sans une certaine bibliothèque que je n'ai pas. Cette chaîne de caractères correspondra au nom du fichier que je passe en entrée.
{
  int nb_char_total = 0;
  int nb_espace = 0;
  int nb_char_fin = 0;
  char caractereActuel;
  char chaine[TAILLE_MAX] = "";
  FILE* fichier = fopen(nom_fichier, "r"); // Pointeur vers le début du fichier (il contient son adresse).
 
  if(fichier != NULL)
  {
    do // Boucle de lecture des caractères un à un.
	  {
      caractereActuel = fgetc(fichier); // On lit le caractère actuel.

      if(caractereActuel == ' ')
      {
        nb_espace++;
        nb_char_total++;
      }
      else { nb_char_total++; }
    }
    while(caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

    while(fgets(chaine, TAILLE_MAX, fichier) != NULL) // On lit une à une les lignes du fichier tant qu'on n'atteint pas la ligne de fin de fichier (NULL).
    {
      nb_char_fin++;
    }

    printf("Le nombre total de caractère(s), d'espace(s) et de caractère(s) fin de ligne dans ce fichier sont respectivement %d, %d et %d. \n", nb_char_total, nb_espace, nb_char_fin);

    fclose(fichier);
  }
  else { printf("Le fichier est vide. \n"); }
}

// 3)
void saut_de_ligne(char nom_fichier[])
{
  char caractereActuel;
  FILE* fichier = fopen(nom_fichier, "r");

  if(fichier != NULL)
  {
    printf("Le contenu du fichier affiché ligne par ligne est : \n \n");

    do
	  {
      caractereActuel = fgetc(fichier);

      if(caractereActuel == ' ') { printf("\n"); /* retour à la ligne */ }
      else { printf("%c", caractereActuel); }
    }
    while(caractereActuel != EOF);

    printf("\n");
  }
  else { printf("Le fichier est vide. \n"); }
}

// III ) TABLEAUX :

// 1)
void fonction1()
{
  int nchiffre[20];
  int i = 1010;
  
  printf("i = %d \n", nchiffre[0]); // L'indice -1 doit correspondre en principe au dernier élément du tableau. Cependant, cela ne marche pas dans repl.it.
  
  for(i = 0; i < 25; i++) // Lorsque le compteur i a dépassé 19, on sort du tableau. Pourtant, on lui demande toujours d'utiliser nchiffre[i] (pour l'afficher et lui affecter la valeur 0). Ce qu'il se passe, c'est que lorsque i est arrivé à 19, on s'est placé sur la zone mémoire allouée à cet élément pour l'utiliser ([etc...|.|.|19|.|.|etc...]). On va alors faire en suivant: on va se placer sur les zones mémoires suivantes et les utiliser, sans pour autant savoir ce qu'il y a dedans. Cependant, il est possible que des données avaient été allouées à ces zones mémoire par d'autres programmes précédemment. Pour éviter ça, on peut utiliser la fonction "malloc(sizeof(structure_de_données))" qui va réserver en mémoire une zone disponible et nécessaire pour enregistrer une certaine 'structure_de _données' dont la taille (en octets) est 'sizeof(structure_de_données)'. Cette fonction renvoie également un pointeur vers cette 'structure_de_données'.
  {
    printf("nchiffre[%d] = %d \n", i, nchiffre[i]);
    
    nchiffre[i] = 0;
  }
}

void fonction2()
{
  fonction1();
  
  printf("Fini. \n");
}

void fonction3()
{
  int i = 1010;
  int nchiffre[20];
  
  printf("i= %d \n", nchiffre[0]);
  
  for (i = 0; i < 25; i++)
  {
    printf("nchiffre[%d] = %d \n", i, nchiffre[i]);
    
    nchiffre[i] = 0;
  }
}

void fonction4()
{
  fonction3();
  
  printf("Fini. \n");
}

// 2)
void etoile(char nom_fichier[])
{
  char caractereActuel;
  char chaine[TAILLE_MAX] = "";
  FILE* fichier = fopen(nom_fichier, "r");

  if(fichier != NULL)
  {
    do
	  {
      caractereActuel = fgetc(fichier);

      if(caractereActuel == ' ') { printf("*"); }
      else { printf("%c", caractereActuel); }
    }
    while(caractereActuel != EOF);

    while(fgets(chaine, TAILLE_MAX, fichier) != NULL)
    {
      printf("*");
    }
  }
  else { printf("Le fichier est vide."); }
}

void affichage_ligne(char nom_fichier[])
{
  char caractereActuel;
  char chaine[TAILLE_MAX] = "";
  FILE* fichier = fopen(nom_fichier, "r");

  if(fichier != NULL)
  {
    while(fgets(chaine, TAILLE_MAX, fichier) != NULL)
    {
      int longueur_chaine = strlen(chaine);

      if( 10 <= longueur_chaine && 20 >= longueur_chaine)
      {
        printf("%s", chaine);
      }
    }
  }
  else { printf("Le fichier est vide."); }
}

void inverser(char nom_fichier[])
{
  char chaine[TAILLE_MAX] = "";
  FILE* fichier = fopen(nom_fichier, "r");

  if(fichier != NULL)
  {
    while(fgets(chaine, TAILLE_MAX, fichier) != NULL)
    {
      int longueur_chaine = strlen(chaine);

      do
	    {
        printf("%c", chaine[longueur_chaine]);
        longueur_chaine--;
      }
      while(longueur_chaine != -1);
    }
  }
  else { printf("Le fichier est vide."); }
}

/* --------------------------------------------------------- */

/* Programme principal permettant de tester mes programmes :

int main()
{
  ();
}

*/