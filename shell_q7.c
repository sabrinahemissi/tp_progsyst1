#include "enseash.h"

int main(void){
	
	int nb_buf, status;
	
	char buf[BUFSIZE] = {0};  
	char stringTemps[10] ={0};
	char * argv[10];
	char * buf_reel;
	
	char * redirectionSortie;
	char * redirectionEntree;
	
	argv[0] = "ls";
	argv[1] = "-l";
	argv[2] = NULL;
	
	struct timespec timeStart, timeStop;
	
	write(STDOUT_FILENO, BIENVENUE, strlen(BIENVENUE)); // On renvoie les messages définis dans le fichier enseash.h
	write(STDOUT_FILENO, SHELL, strlen(SHELL));
	
	while(1){
		nb_buf = read(STDIN_FILENO, buf, BUFSIZE); 
	
		// On met une fin de chaine de carac après l'entrer de l'utilisateur
		buf[nb_buf-1]='\0';
		
		
		if(strcmp(buf,"exit")==0 || nb_buf==0){
			
			write(STDOUT_FILENO, EXIT, strlen(EXIT));
			kill(0,SIGINT); 
		}
		clock_gettime(CLOCK_REALTIME, &timeStart); 

		if(fork()==0){ //On est dans le fils
			
			//On améliore encore notre micro shell en implémentant la possibilité d'utiliser des redirections, comme '<' et '>' :
			
			
			buf_reel = strtok(buf, ">"); //Avec strtok, on recherche ">"
			redirectionSortie = strtok(NULL, ">");
			
			//Si on a ">", alors on ouvre un fd vers le fichier
			if(redirectionSortie != NULL){ 
				int fdS = open(redirectionSortie, O_CREAT|O_RDWR|O_CLOEXEC,S_IRWXG|S_IRWXU|S_IRWXO); //Ouverture du fd vers un fichier
				dup2(fdS,STDOUT_FILENO); //Duplique le fd
				close(fdS); //Fermeture de la sortie standard
			}
				
				
			buf_reel = strtok(buf, "<"); //Avec strtok, on recherche "<"
			redirectionEntree = strtok(NULL, "<");	
			
			//Si on a "<", alors on ouvre un fd vers le fichier	
			if(redirectionEntree != NULL){ 
				int fdE = open(redirectionEntree,O_CREAT|O_RDWR);
				close(STDIN_FILENO); //Fermeture de l'entrée standard
				dup2(fdE,STDIN_FILENO); //Duplication : le fd remplace la sortie standard
				close(fdE); //Fermeture du fd
			}	
			
			
			argv[0]=strtok(buf_reel," ");
			
            int i=0;
            while((argv[i]!=NULL)){
                i=i+1;
                argv[i]=strtok(NULL," ");
            }
			execvp(argv[0],argv); //Appel plus performant, gestion des paramètres d'entrées multiples
			
			write(STDOUT_FILENO, COMMANDE_INCONNUE, strlen(COMMANDE_INCONNUE));
			write(STDOUT_FILENO, SHELL, strlen(SHELL));
		}
		
		else{ //On est dans le père
			
			wait(&status);
			
			clock_gettime(CLOCK_REALTIME, &timeStop); 
			
			if(WIFEXITED(status)){
				write(STDOUT_FILENO,RETOUR,strlen(RETOUR));
				
				sprintf(stringTemps,"%d|%ldms",WEXITSTATUS(status), (timeStop.tv_nsec - timeStart.tv_nsec)/1000000); 
				write(STDOUT_FILENO,stringTemps,strlen(stringTemps));
				
				write(STDOUT_FILENO,FIN,strlen(FIN));
			}
		
			if(WIFSIGNALED(status)){
				write(STDOUT_FILENO,SIGNAL,strlen(SIGNAL));
				
				sprintf(stringTemps,"%d|%ldms",WEXITSTATUS(status), (timeStop.tv_nsec - timeStart.tv_nsec)/1000000); 
				write(STDOUT_FILENO,stringTemps,strlen(stringTemps));
				
				write(STDOUT_FILENO,FIN,strlen(FIN));
			}
		}
	}
	
	return 0;
}


//On vérifie avec les commandes :  
// - ls > filelist.txt
// - wc -l < filelist.txt

// Ces commandes s'effectuent bien 
