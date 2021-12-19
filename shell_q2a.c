#include "enseash.h"


int main(void){
	char buf[BUFSIZE];
	write(STDOUT_FILENO, SHELL, strlen(SHELL));
	read(STDIN_FILENO, buf, BUFSIZE);
	return 0;
	
}

