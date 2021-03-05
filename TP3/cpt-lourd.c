#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h>
#include <sys/wait.h> 
#define NB_PROCESSUS 500 

int pid_fils, i, somme;

/*

int main()
{ 
	somme = 0;
	
  for(i=0 ; i < NB_PROCESSUS ; i++)
  { 
		pid_fils = fork(); // La fonction "fork()" permet, lorsqu'elle est appelée au sein d'un programme en cours d'exécution (un processus), de le dupliquer. Ce processus dupliqué (ici, le programme main) correspondra au processus père, et sa copie conforme nouvellement créée sera son fils. Si fork() est appelée dans le processus père elle renvoie le pid de son fils, mais si elle est appelée dans ce dernier, elle renverra 0.
		
    // Le processus père vient de créer un nouveau processus fils qui démare ici. On se situe dans le processus fils à partir d'ici. Au moment où il est créé, il exécute aussi le fork et renvoie 0 dans sa propre variable pid_fils.

    if(pid_fils == 0) // Le processus père ne rentre pas ici puisque son fork renvoie le pid du fils, mais le processus fils lui rentre dedans car son fork renvoie 0.
    { 
		  somme++;
		  
      printf("Je suis le processus fils d'indice %d : somme = %d. \n", i, somme);
   
      exit(0); // Cette fonction permet de mettre fin au processus fils courant en renvoyant un code de retour. Ce code de retour, passé en paramètre de la fonction exit, permet de spécifier comment le programme se termine. Une valeur nulle (0 ou la constante "EXIT_SUCCESS") indique au système d'exploitation que l'exécution de ce programme s'est bien déroulée. Tout autre valeur indique une sortie anormale du programme (la constante "EXIT_FAILURE" peut aussi être utilisée).
		}
    // Une fois que le processus père a créé un nouveau processus fils, celui-ci commence à s'exécuter et il se finira au exit(0). Le père continue à s'exécuter en parallèle et continue donc de créer les processus fils restants.

    else { printf("Le pid du processus fils nouvellement créé est %d. \n", pid_fils); }
  }

  while(wait(0) != -1) { }; // Remarque: NULL est un pointeur constant dont la valeur (qui est une adresse donc) est 0. On aurait donc pu remplacer le paramètre 0 par NULL.

  printf("Je suis le processus père : somme = %d. De plus, mon pid est %d. \n", somme, getpid());

   // Le processus père a exécuté la fonction "wait()". Cette fonction permet la synchronisation entre le processus père et tous ses processus fils: elle reçoit un signal émis par le premier processus fils ayant fini de s'exécuter (ce qui la déclenche) et prend en paramètre l'adresse d'une variable dans laquelle est mis le code retour (qui est donc 0 pour tous les processus fils créés) de ce processus fils. Elle met également en pause le processus père (dans ce cas, on dit qu'il "dort") et elle renvoie le pid du processus fils qui l'a déclenché. Elle compare alors ce pid à -1: si celui est différent de -1, le processus père s'éveille et ré-itère le wait qui attend à nouveau le prochain processus fils et ainsi de suite jusqu'au dernier, après quoi le wait renvoie -1 car il n'y a plus de processus fils. Le processus père se réveille alors définitivement et finit à son tour sa propre exécution: c'est pour cela que c’est toujours la ligne du processus père qui s’affiche en dernier.
  
  return 0;
}

*/