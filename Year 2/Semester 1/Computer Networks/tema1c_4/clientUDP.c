#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main(){

	int s,l;
	struct sockaddr_in server;
	l=sizeof(server);

	if((s=socket(AF_INET,SOCK_DGRAM,0))<0){
		printf("Eroare la creare socket\n");
		return 1;
	}

	memset(&server,0,sizeof(server));
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(1234);

	char sir[101];
	uint16_t dimensiune;

	printf("Dati sir\n");
	scanf("%s",sir);

	dimensiune=strlen(sir);
	dimensiune=htons(dimensiune);
	sendto(s,&dimensiune,sizeof(dimensiune),0,(struct sockaddr*)&server,l);
	dimensiune=ntohs(dimensiune);
	sendto(s,sir,dimensiune+1,0,(struct sockaddr*)&server,l);

	recvfrom(s,sir,dimensiune+1,MSG_WAITALL,(struct sockaddr*)&server,&l);

	printf("Oglindit = %s\n",sir);

	close(s);
	return 0;
}
