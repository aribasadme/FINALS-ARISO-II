#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 80

void alarma(int sig){
	char buff[SIZE];
	sprintf(buff,"Error reading command input Timeout period expired\n");
	write(1,buff,strlen(buff));
	exit(1);
}

int main(int arg, char *argv[]){
	char buff[SIZE], c;
	int i;
	signal(SIGALRM, alarma);
	alarm(10);
	i = 0;
	while ( read(0, buff, 1) > 0 ){
		if (c!='\n') buff[i++]=c;
		else break;
	}
	alarm(0);
	procesar_linea(buff);
}
