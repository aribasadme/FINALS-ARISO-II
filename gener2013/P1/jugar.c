#include <stdlib.h>
#include <stdio.h>

#define N 3

int main(){
	int elecc;
	srand(getpid());
	elecc = rand() % N;
	exit(elecc);
}