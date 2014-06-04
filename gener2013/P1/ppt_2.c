#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define F 1
#define N 0
#define M 80

int main(int argc, char *argv[]){
	int i, fd, pid1, pid2, estado, n, jugador1, jugador2;
	char buf[M];
	
	if (argc != 2){
		fprintf(stderr, "USO: %s fichero\n", argv[N]);
		exit(1);
	}
	for (i=0; i<2; i++)
		if (fork() == 0){
			execl("./jugar","jugar",NULL);
			fprintf(stderr,"ERROR fork\n");
			exit(1);
		}
	
	if ( (fd = open(argv[F], O_WRONLY|O_CREAT|O_APPEND, 0666)) < 0){
		fprintf(stderr,"ERROR open");
		exit(1);
	}
	
	pid1 = wait(&estado);
	jugador1 = WEXITSTATUS(estado);
	n = sprintf(buf,"% d: ",pid1);
	write (fd, buf, n);
	switch (jugador1){
		case 0:			write (fd, "piedra\n", strlen("piedra\n")); break;
		case 1:			write (fd, "papel\n", strlen("papel\n")); break;
		case 2:			write (fd, "tijera\n", strlen("tijera\n")); break;
	}

	pid2 = wait(&estado);
	jugador2 = WEXITSTATUS(estado);
	n = sprintf(buf,"% d: ",pid2);
	write (fd, buf, n);
	switch (jugador1){
		case 0:			write (fd, "piedra\n", strlen("piedra\n")); break;
		case 1:			write (fd, "papel\n", strlen("papel\n")); break;
		case 2:			write (fd, "tijera\n", strlen("tijera\n")); break;
	}

	if (jugador1==0 && jugador2==2 || jugador1==2 && jugador2==1 || jugador1==1 && jugador2==0)
		n = sprintf(buf, "Ganador pid: %d\n", pid1);
	else if (jugador1==0 && jugador2==1 || jugador1==2 && jugador2==0 || jugador1==1 && jugador2==2)
		n = sprintf(buf, "Ganador pid: %d\n", pid2);
	else	n = sprintf(buf, "Empate\n");

	write(fd, buf, n);

	exit(0);
}
