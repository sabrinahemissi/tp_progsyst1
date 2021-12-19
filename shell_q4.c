#include "enseash.h"

int main(void){
	
	int nb_buf, status;
	char buf[BUFSIZE];  
	char stringSTATUS[1] ={0};
	
	write(STDOUT_FILENO, BIENVENUE, strlen(BIENVENUE)); // On renvoie les messages définis dans le fichier enseash.h
	write(STDOUT_FILENO, SHELL, strlen(SHELL));
	
	while(1){
		nb_buf = read(STDIN_FILENO, buf, BUFSIZE); 
	
		
		// On met une fin de chaine de carac après l'entrer de l'utilisateur
		buf[nb_buf-1]='\0';
		
		
		if(strcmp(buf,"exit")==0 || nb_buf==0){
			//exit si la commande est exit ou si on effectue "Ctrl+D"
			
			write(STDOUT_FILENO, EXIT, strlen(EXIT));
			kill(0,SIGINT); //utilise les appels système 
		}

		if(fork()==0){
		//On sait que si fork() ==0, on est dans le fils. On execute donc la commande :
			
			execlp(buf, buf,NULL);
			write(STDOUT_FILENO, COMMANDE_INCONNUE, strlen(COMMANDE_INCONNUE));
			write(STDOUT_FILENO, SHELL, strlen(SHELL));
		}
		
		else{
		//On sait qu'on est ici dans le père, c'est ici que l'on va afficher le code de retour de la commande précédente (ou du signal) dans le prompt, car en revenant dans le père et après avoir attendu (avec 'wait(&status)), on sait que les commandes sont effectuées :
			
			wait(&status);
			if(WIFEXITED(status)){
				write(STDOUT_FILENO,RETOUR,strlen(RETOUR));
				
				stringSTATUS[0]=(WTERMSIG(status)&0xf) +'0';
				write(STDOUT_FILENO,stringSTATUS,1);
				
				write(STDOUT_FILENO,FIN,strlen(FIN));
			}
		
			if(WIFSIGNALED(status)){
				write(STDOUT_FILENO,SIGNAL,strlen(SIGNAL));
				
				stringSTATUS[0]=(WTERMSIG(status)&0xf) +'0';
				write(STDOUT_FILENO,stringSTATUS,1);
				
				write(STDOUT_FILENO,FIN,strlen(FIN));
			}
		}
	}
	
	return 0;
}
