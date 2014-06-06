#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char *argv[]){

	int sock, PORT = 10000;
	struct sockaddr_in addr;

	if (argc != 4){	fprintf(stderr,"Uso: %s cmd arg1 @IP\n",argv[0]); exit(1); }
	
	memset (&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	inet_aton(argv[3], &(addr.sin_addr));

	if (fork() == 0){
		sock = socket(AF_INET,SOCK_STREAM,0);
		if (connect (sock, (struct sockaddr *) &addr, sizeof(addr)) < 0){ printf("ERROR connect\n"); exit(-1); }
		close(1);
		dup(sock);
		close(sock);
		if (execlp(argv[1],argv[1],argv[2],NULL) < 0){ exit(-1); }
	}
	wait(NULL);
	printf("comando ejecutado\n");
}
