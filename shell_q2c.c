#include "enseash.h"




int   main ( void )
{
    
    write(STDOUT_FILENO, BIENVENUE, strlen(BIENVENUE));
	write(STDOUT_FILENO, SHELL, strlen(SHELL)); // On renvoie les messages définis dans le fichier enseash.h
	
    char buf[BUFSIZE];
	
	while(1)
	{
		read(STDIN_FILENO, buf, BUFSIZE);
		int pid, status;
		pid=fork();
	
		if (fork==0) 
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

		
