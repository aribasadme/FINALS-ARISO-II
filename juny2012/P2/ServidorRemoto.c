#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define NSmax 10

int ns_activos = 0;

void ras_sigchild(int sig){
	wait(NULL);
	ns_activos--;
}

int main (int argc, char *argv[]){
	struct sockaddr_in lsa, csa;
	int len = sizeof(struct sockaddr_in);
	int lsd, csd;
	int PORT = 10000;
	char c;
	struct sigaction act;

	act.sa_handler = ras_sigchild;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD,&act,NULL);

	memset(&lsa,0,sizeof(lsa));
	lsa.sin_family = AF_INET;
	lsa.sin_port=htons(PORT);
	lsa.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if ((lsd=socket(AF_INET,SOCK_STREAM,0)) < 0){ fprintf(stderr,"ERROR socket\n"); exit(1);	}
	if (bind(lsd, (struct sockaddr *) &lsa, sizeof(lsa)) < 0){ fprintf(stderr,"ERROR bind\n"); exit(1); }
	if (listen(lsd, 10) < 0){	fprintf(stderr,"ERROR listen\n"); exit(1);	} 

	for (;;){
		if ( (csd=accept(lsd, (struct sockaddr *)&lsa, &len)) < 0) {	fprintf(stderr,"ERROR accept\n"); exit(1);	}
		if (ns_activos < NSmax){
			if (fork()==0){
				close(lsd);
				while(read(csd,&c,1)>0) write(1,&c,1);
				close(csd);
				exit(0);
			}
			ns_activos++;
		}
		close(csd);
	}
}
