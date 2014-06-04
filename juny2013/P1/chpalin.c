#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define M 80

int main (int argc, char *argv[]){
	char f[M], g[M];
	int len, fd, a, b, c, d, m;

	if (argc != 2){ fprintf(stderr, "USO INCORRECTO de chpalin!\n"); exit(2); }

	if ( (fd = open(argv[1], O_RDONLY)) <0) fprintf(stderr, "ERRROR open\n");
	a = 0;
	c = 1;
	d = 0;
	while ( (read(fd, &f[a], sizeof(char))) != 0){
			while (f[a] == ' ')							// Suprimeixo els espais
				read(fd, &f[a], sizeof(char));
			if( f[a] != '\n'){							
				a++;
			}
			else {										
				len = a;
				f[len] = '\0';							// Acabo la linia
				for ( b=0; b<len; b++)					// Inverteixo f[] i la copio a g[]
					g[b] = f[len-1-b];
				g[len] = '\0';
						
				switch (fork()){
					case -1: fprintf(stderr,"ERROR fork\n"); exit(2);
					case 0:
						execl("./cequals", "cequals", f, g, NULL);
					default:
						wait(&m);
						if( WEXITSTATUS(m)==1 ){ 
							d++;	// Actualitzo comptador de palindroms
							fprintf(stdout, "La frase %d es palindroma\n",c);
						}
						else fprintf(stdout,"La frase %d NO es palindroma\n",c);
						c++;
				}
				a = 0;
			}
	}
	fprintf(stdout,"%d palindromas\n", d);
	exit(0);
}
