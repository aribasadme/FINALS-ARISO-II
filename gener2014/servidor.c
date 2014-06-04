#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#define BUFSIZE 512

int main(int argc, char *argv[]){
	int socks, sockd, port, clilen, len;
	struct sockaddr_in servaddr, cliaddr;
	char mensaje[BUFSIZE];

	assert(argc==2);
	port = atoi(argv[1]);
	
	if ( (socks = socket(AF_INET, SOCK_STREAM,0)) < 0) fprintf(stderr,"ERROR socket\n");

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	if ( bind(socks, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) fprintf(stderr,"ERROR bind\n");
	if ( listen(socks, 5) < 0) fprintf(stderr,"ERROR listen\n");

	for(;;){
		clilen = sizeof(cliaddr);
		if ( (sockd = accept(socks, (struct sockaddr *) &cliaddr, &clilen)) < 0) fprintf(stderr,"ERROR accept\n");
		switch (fork()){
			case -1: fprintf(stderr,"ERROR fork\n"); break;
			case 0:
					close(socks);
					len = read(sockd, mensaje, BUFSIZE);
					if ( len<0 ) fprintf(stderr,"ERROR read\n");
					if ( write(1, mensaje, len) <0 )	fprintf(stderr,"ERROR write\n");
					close(sockd);
					exit(0);
			default: close(sockd);	
		}
	}
}
