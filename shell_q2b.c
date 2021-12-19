#include "enseash.h"




int   main ( void ){
    
    write(STDOUT_FILENO, BIENVENUE, strlen(BIENVENUE));
	write(STDOUT_FILENO, SHELL, strlen(SHELL));
	
    char buf[BUFSIZE];
	
	read(STDIN_FILENO, buf, BUFSIZE);
	
	int pid, status;
	
	pid=fork();
	
	if (fork==0){
		execlp(buf,buf,NULL);
		write(STDOUT_FILENO, COMMANDE_INCONNUE, strlen(COMMANDE_INCONNUE));
		
	} else { 
		
		wait(&status);
	}
	return 0;
}

		
		
