#include "enseash.h"


int   main ( void )
{
    
    write(STDOUT_FILENO, BIENVENUE, strlen(BIENVENUE));
	write(STDOUT_FILENO, SHELL, strlen(SHELL)); // 0n renvoie les messages définis dans le fichier enseash.h
	
    char buf[BUFSIZE];
    int nb_buf;
	
	while(1)
	{
		nb_buf=read(STDIN_FILENO, buf, BUFSIZE);
		int pid, status;
		pid=fork();
		buf[nb_buf-1]='\0'; // On met une fin de chaîne de caractère après l'entrée de l'utilisateur
		
		if(strcmp(buf,"exit")==0 || nb_buf==0)
		{
			write(STDOUT_FILENO, EXIT, strlen(EXIT));
			kill(0,SIGINT);
			
		}
		if(fork==0)
		{ 
			execlp(buf,buf,NULL);
			write(STDOUT_FILENO, COMMANDE_INCONNUE, strlen(COMMANDE_INCONNUE));
			write(STDOUT_FILENO, SHELL, strlen(SHELL));
		}
		
		else 
		{
			wait(&status);
		}
		
	}
	return 0;
}

		
