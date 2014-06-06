#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define M 10

int main(int argc, char *argv[]){
	char *com[M];
	int i, fd[2];

	if (argc >= 3 && argc <= M-1){
		for (i=0; i<argc; i++) com[i]=argv[i];
		com[i] = NULL;
		
		pipe(fd);
		switch (fork()){
			case -1: fprintf(stderr,"ERROR fork\n"); exit(1);
			case 0:
					dup2(fd[1],1);
					close(fd[0]);
					close(fd[1]);
					com[0] = "./a";
					fprintf(stderr,"PID: %d ejecuto: %s paso a ejecutar: %s\n",getpid(),argv[0],com[0]);
					execv(com[0],&com[0]);
			default:
					dup2(fd[0],0);
					close(fd[0]);
					close(fd[1]);
					com[0] = "sort";
					fprintf(stderr,"PID: %d ejecuto: %s paso a ejecutar: %s\n",getpid(),argv[0],com[0]);
					execlp(com[0], "sort","-n","-r",NULL);
		}
	}
	exit(0);
}
