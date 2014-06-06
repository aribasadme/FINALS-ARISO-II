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
	int i;

	if (argc >= 3 && argc <= M-1){
		com[0] = "linec";
		for (i=0; i<argc; i++) com[i]=argv[i];
		com[i] = NULL;
		fprintf(stderr,"PID: %d ejecuto: %s paso a ejecutar: %s\n",getpid(),argv[0],com[0]);
		execv(com[0], &com[0]);
	}
	exit(0);
}
