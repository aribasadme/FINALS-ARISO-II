#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

int main (int argc, char *argv[]){
	int a, b, k, n, fd;
	float xk,X, F, area, integral;
	
	a=0;
	b=1;

	assert(argc==4);

	n = atoi(argv[2]);
	k = atoi(argv[3]);

	/* Base de los triangulos */
	X = (float)(b-a)/n;		
	xk = a + k*X;
	if (k == n) xk = 1;			

	/* Calculo de f(xk) = 4/(1+xk²) */
	F = 4/(1 + xk*xk);		
	
	/* Area del triangulo de base X y altura f(xk) */
	area = X*F;		

	if ((fd = open(argv[1],O_RDWR,0777))<0) fprintf(stderr,"ERROR open\n");
	if(read(fd,&integral,sizeof(integral))<0) fprintf(stderr, "ERROR read\n");
	
	integral += area;													/*	Acumula el valor */

	if((lseek(fd,0,SEEK_SET))<0) fprintf(stderr,"ERROR lseek\n");
	if(write(fd,&integral, sizeof(integral))<0) fprintf(stderr,"ERROR write\n");

	exit(0);
}
