#include "enseash.h"


int main(void){
	int i;
	char c;
	while(1){		
	write(STDOUT_FILENO, SHELL, strlen(SHELL));
	i = read(STDIN_FILENO, c, strlen(c));
	c[i-1]= '\0';
}
	return 0;
}
