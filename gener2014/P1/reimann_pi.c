#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#define MAX 10000	//numero maximo de rectangulos
#define BUF 256

int main(int argc, char *argv[])
{
	int n, fd, k;
	float integral = 0.0;
	char nh[BUF];
	
	assert(argc == 3);
	n = atoi(argv[2]);

	if (n > MAX){	fprintf(stderr,"n demasiado grande\n"); exit(0); }
	
	if ((fd = open(argv[1], O_WRONLY|O_CREAT, 0777)) < 0) { fprintf(stderr, "ERROR crear"); exit(0); }
	
	if(write(fd, &n, sizeof(n)) < 0) printf("ERROR write\n");
	if(close(fd) < 0) printf("ERROR close\n");

	for (k=1; k<=n ; k++){
		switch(fork()){
			case -1: fprintf(stderr,"ERROR fork\n"); exit(-1);
			case 0:
					snprintf(nh, BUF, "%d", k);
					execl("./cac_area", "cac_area", argv[1], argv[2], nh, NULL);
					exit(0);
			default:
					wait(NULL);
		}

	}
	if ((fd = open(argv[1], O_RDONLY)) < 0) fprintf(stderr, "ERROR opne\n");
	if( read(fd, &integral, sizeof(integral)) < 0) fprintf(stderr,"ERROR read\n");

	printf("\nLa aproximacion calculada de PI es: %f\n", integral);

	exit(0);
}
