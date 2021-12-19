#include "enseash.h"


int main(void){
	write(STDOUT_FILENO, BIENVENUE, strlen(BIENVENUE));
	write(STDOUT_FILENO, SHELL, strlen(SHELL));
	return 0;
} 
