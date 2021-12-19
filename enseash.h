#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>

#define BIENVENUE "$ ./enseash\nBienvenue dans le Shell ENSEA. \nPour quitter, tapez 'exit'.\n"
#define SHELL "enseash % " //Création d'une etiquette différente car réutilisée dans d'autres questions
#define EXIT "Bye Bye. \n$\n"
#define RETOUR "enseash [exit:"
#define SIGNAL "enseash [sign:"
#define FIN "] %"



#define BUFSIZE 128

#define COMMANDE_INCONNUE "Commande non trouvée.\n"
