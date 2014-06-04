#include <stdio.h>
#include <stdlib.h>
#define FINCAD '\0'

int main (int argc, char *argv[]){
	int i;
	
	if (argc != 3){ fprintf(stderr, "USO INCORRECTO de cequals!\n"); exit(2); }
	for (i=0; argv[1][i] != FINCAD && argv[1][i] == argv[2][i]; i++);
	if (argv[1][i] == argv[2][i])
		exit(1);
	else
		exit(0);
}
