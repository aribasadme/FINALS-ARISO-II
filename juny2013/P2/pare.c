#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void barajar(int num, int *vector);
void handler(int alguno){
	printf("Soy %d y me han matado\n",getpid());
	exit(-1);
}

main(){
	int pids[20], fd[2];
	int i, leido, muerto;
	sigset_t set;

	pipe(fd);
	for (i=0; i<20; i++){
		pids[i] = fork();
		if (pids[i] == 0)		// Hijos
		{
			signal(SIGUSR1, handler);
			close(fd[1]);
			sigemptyset(&set);
			sigaddset(&set, SIGUSR1);
			printf("Hijo %d antes de leer\n", getpid());
			sigprocmask(SIG_BLOCK, &set, NULL);
			read (fd[0], &leido, sizeof(int));
			close(fd[0]);
			printf("Hijo %d despues de leer, voy a matar a %d\n", getpid(),leido);
			kill(leido,SIGUSR1);
			sigprocmask(SIG_UNBLOCK, &set, NULL);
			pause();
		}
		printf("Creado hijo %d\n",pids[i]);	
	}
	close(fd[0]);
	barajar(20,pids);
	write(fd[1],pids,20*sizeof(int));
	close(fd[1]);
	for (i=0; i<20; i++)
	{
		muerto = wait(NULL);
		printf("El hijo %d ha puerto\n",muerto);
	}
	exit(0);
}
