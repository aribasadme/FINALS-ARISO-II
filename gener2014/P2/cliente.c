#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <assert.h>

#define BUFSIZE 512

int main (int argc, char *argv[]){
	int sock, len, port;
	struct sockaddr_in addr;
	struct hostent *host;
	char transmite[BUFSIZE];

	assert(argc==3);	
	port = atoi(argv[2]);
	host = gethostbyname(argv[1]);

	if( (sock = socket(AF_INET,SOCK_STREAM,0)) <0) fprintf(stderr,"ERROR socket\n");
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	memcpy(&addr.sin_addr, host->h_addr, host->h_length);
	addr.sin_port = htons(port);

	if( connect(sock, (struct sockaddr*) &addr, sizeof(addr)) <0) fprintf(stderr,"ERROR connect\n");
	
	write(1,"Introduzca un mensaje: ", strlen("Introduzca un mensaje: "));
	if(	(len = read(0, transmite, BUFSIZE)) < 0) fprintf(stderr, "ERROR read STDIN\n");
	if( write(sock,transmite,len) < 0) fprintf(stderr, "ERROR write socket\n");
		
	close(sock);
}
