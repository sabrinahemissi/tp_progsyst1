#include "enseash.h"

int main(void){
	
	int nb_buf, status;
	char buf[BUFSIZE]; 
	char stringTemps[10] ={0};
	
	
	struct timespec timeStart, timeStop; //Structures servant à capturer le temps de départ et d'arrivée
	
	write(STDOUT_FILENO, BIENVENUE, strlen(BIENVENUE)); // On renvoie les messages définis dans le fichier enseash.h
	write(STDOUT_FILENO, SHELL, strlen(SHELL));
	
	while(1){
		nbChar = read(STDIN_FILENO, buf, BUFSIZE); 
		
		
		 // On met une fin de chaine de carac après l'entrer de l'utilisateur
		buf[nb_buf-1]='\0';
		
		
		if(strcmp(buf,"exit")==0 || nb_buf==0){
			//Ici on veut que si la commande demandée par l'utilisateur est 'exit', alors on exécute exit.
			
			write(STDOUT_FILENO, EXIT, strlen(EXIT));
			kill(0,SIGINT); 
		}
		
		clock_gettime(CLOCK_REALTIME, &timeStart); //Capture du temps de départ

		if(fork()==0){
			//On sait que si fork()==0, on est dans le fils. On execute donc la commande.
						
			execlp(buf, buf,NULL);
			
			write(STDOUT_FILENO, COMMANDE_INCONNUE, strlen(COMMANDE_INCONNUE));
			write(STDOUT_FILENO, SHELL, strlen(SHELL));
		}
		
		else{
			//On améliore ici le programme du père en ajoutant l'affichage du temps d'execution de la commande :
			
			wait(&status);
			
			clock_gettime(CLOCK_REALTIME, &timeStop); //Capture du temps d'arrivée
			
			if(WIFEXITED(status)){
				write(STDOUT_FILENO,RETOUR,strlen(RETOUR));
				
				sprintf(stringTemps,"%d|%ldms",WEXITSTATUS(status), (timeStop.tv_nsec - timeStart.tv_nsec)/1000000); //On vient ici renvoyer le temps d'éxécution d'une commande en le calculant : temps d'arrivée - temps de départ
				
				write(STDOUT_FILENO,FIN,strlen(FIN));
			}
		
			if(WIFSIGNALED(status)){
				write(STDOUT_FILENO,SIGNAL,strlen(SIGNAL));
				
				sprintf(stringTemps,"%d|%ldms",WEXITSTATUS(status), (timeStop.tv_nsec - timeStart.tv_nsec)/1000000); //On vient ici renvoyer le temps d'éxécution d'une commande en le calculant : temps d'arrivée - temps de départ
				write(STDOUT_FILENO,stringTemps,strlen(stringTemps));
				
				write(STDOUT_FILENO,FIN,strlen(FIN));
			}
		}
	}
	
	return 0;
}
