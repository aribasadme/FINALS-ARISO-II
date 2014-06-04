#include <unistd.h>
#include <signal.h>

void barajar(int num, int *vector);
void handler(int alguno){
	printf("Soy %d y me han matado\n");
	exit(-1);
}

main(){
	int pids[20], fd[2];
	int i, leido, muerto;
	sigset_t set;

	pipe(fd);
	for (i=0; i<20; i++){
		pids[i] = fork();
		if (pid[i] == 0)		// Hijos
		{
			signal(SIGUSR1, handler);
			close(fd[1]);
			sigemptyset(&set);
			sigaddset(&set, SIGUSR1);
			printf("Hijo %d antes de leer\n", getpid());
			sigprocmask(SIG_BLOCK, &set, NULL);
			read (fd[0], &leido, sizeof(int));
			close(fd[0]);
		{	
	}

}
