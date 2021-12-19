#include "enseash.h"




int   main ( void )
{
    
    write(STDOUT_FILENO, BIENVENUE, strlen(BIENVENUE));
	write(STDOUT_FILENO, SHELL, strlen(SHELL)); // on renvoie les messages définis dans le fichier enseash.h
	
    char buf[BUFSIZE];
    int nb_buf;
    char stringSTATUS[1]={0};

	
	while(1)
	{
		
		int pid, status;
		
		nb_buf=read(STDIN_FILENO, buf, BUFSIZE);
		pid=fork();
		buf[nb_buf-1]='\0'; // on définit une fin de chaîne de caractère après l'entrée de l'utilisateur
		
		if(strcmp(buf,"exit")==0 || nb_buf==0)
		{
			write(STDOUT_FILENO, EXIT, strlen(EXIT));
			kill(0,SIGINT);
		}
		
		
		if (pid!=-1){
			
			if(pid==0)
			{ 
				execlp(buf,buf,NULL);
				write(STDOUT_FILENO, COMMANDE_INCONNUE, strlen(COMMANDE_INCONNUE));
				write(STDOUT_FILENO, SHELL, strlen(SHELL));
			}
		
		
		
			if(pid >0) // Lorsque le pid=0 fork()=0 donc aucune commande n'est éxécutée on attend alors la commande suivante #wait 
			{
				wait(&status);
			
			
			
			if (WIFEXITED(status))
			{
				write(STDOUT_FILENO, RETOUR, strlen(RETOUR));
				printf("code exit : %d\n",WEXITSTATUS(status));
				write(STDOUT_FILENO, stringSTATUS, 2);
				write(STDOUT_FILENO, FIN, strlen(FIN));
			}
			
			
			if (WIFSIGNALED(status))
			{
				write(STDOUT_FILENO, SIGNAL, strlen(SIGNAL));
				printf("code exit : %d\n",WTERMSIG(status));
				write(STDOUT_FILENO, stringSTATUS, 2);
				write(STDOUT_FILENO, FIN, strlen(FIN));
			}
		
		
		}
		}
		
}
}
