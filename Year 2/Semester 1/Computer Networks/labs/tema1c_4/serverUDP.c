#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

void oglindit(char* sir){

	int lungime = strlen(sir);
	for(int i=0;i<lungime/2;i++){
		char aux = sir[i];
		sir[i] = sir[lungime-i-1];
		sir[lungime-1-i] = aux;
	}
}

int main(){

	int s,l;
	struct sockaddr_in server,client;
	l=sizeof(client);

	if((s=socket(AF_INET,SOCK_DGRAM,0))<0){
		printf("Eroare la creare socket\n");
		return 1;
	}

	memset(&server,0,sizeof(server));
	memset(&client,0,l);
	server.sin_addr.s_addr = inet_addr("0.0.0.0");
	server.sin_family = AF_INET;
	server.sin_port = htons(1234);

	if(bind(s,(struct sockaddr*)&server,sizeof(server))<0){
		printf("Eroare la bind\n");
		return 1;
	}

	while(1){
		printf("Astept clienti...\n");
		uint16_t dimensiune;
		char* sir;

		recvfrom(s,&dimensiune,sizeof(dimensiune),MSG_WAITALL,(struct sockaddr*)&client,&l);

		dimensiune = ntohs(dimensiune);

		sir = (char*)malloc(sizeof(char) * (dimensiune+1));

		recvfrom(s,sir,dimensiune,MSG_WAITALL,(struct sockaddr*)&client,&l);
		sir[dimensiune]='\0';
		printf("Am primit: %s\n",sir);
		oglindit(sir);

		printf("Oglindit: %s\n",sir);

		sendto(s,sir,dimensiune+1,0,(struct sockaddr*)&client,l);

		free(sir);
	}

	close(s);
	return 0;
}
