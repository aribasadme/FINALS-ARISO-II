#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 80

void rut_sigusr1(int sig)
{
	char c, prog[SIZE], input[SIZE], outpu[SIZE];
	int fd, n, i=0;

	if ( (fd=open("./Fichero", O_RDONLY)) < 0) { fprintf(stderr,"ERROR open\n"); exit(1); }
	while ( (n=read(fd,&c,sizeof(char)) > 0){
		if (c!='\n') prog[i++] = c;
		else break;
	}
	prog[i] = '\0';
	i = 0;
	while ( (n=read(fd,&c,sizeof(char)) > 0){
		if (c!='\n') input[i++] = c;
		else break;
	}
	input[i] = '\0';
	i = 0;
	while ( (n=read(fd,&c,sizeof(char)) > 0){
		if (c!='\n') output[i++] = c;
		else break;
	}
	output[i] = '\0';
	
	switch (fork()){
		case -1:	fpritnf(stderr,"ERROR fork\n"); exit(1);
		case 0:		if ( strcmp(input,"herencia") != 0){
						close(0);
						open(input,O_RDONLY);
					}
					if( strcmp(output,"herencia") != 0={
						close(1);
						open(output,O_RD_ONLY);
					}
					execlp(prog, prog, NULL);
					exit(-1);
		default: break;
	}
}

main (){
	signal(SIGUSR1,rut_sigusr1);
	while(1) pause();
}