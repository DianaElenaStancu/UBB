/*
Un client trimite unui server un sir de caractere. Serverul va returna clientului numarul de caractere spatiu din sir.
*/
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>

void deservire_client(int c){
	uint16_t dimensiune,rezultat=0;
	char x;
	recv(c,&dimensiune,sizeof(dimensiune),MSG_WAITALL);
	dimensiune=ntohs(dimensiune);
	printf("Dimensiune sir = %hu\n",dimensiune);
	for(int i=0;i<dimensiune;i++){
		recv(c,&x,sizeof(x),MSG_WAITALL);
		printf("x = %c\n",x);
		if(x==' ')
			rezultat++;
	}

/*	recv(c,x,dimensiune+1,MSG_WAITALL);
	for(int i=0;i<=dimensiune;i++){
		if(x[i]==' ')
			rezultat++;
	}
*/
	rezultat=htons(rezultat);
	send(c,&rezultat,sizeof(rezultat),0);
	close(c);
}

int main(){

	int s,c;
	struct sockaddr_in server,client;
	int l=sizeof(client);

	if((s=socket(AF_INET,SOCK_STREAM,0))<0){
		printf("Eroare la creare socket\n");
		return 1;
	}

	memset(&server,0,sizeof(server));
	memset(&client,0,sizeof(client));
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_family=AF_INET;
	server.sin_port=htons(8888);

	if(bind(s,(struct sockaddr*)&server,sizeof(server))<0){
		printf("Eroare la bind\n");
		return 1;
	}

	listen(s,5);

	while(1){
		printf("Se asteapta clienti....\n");
		c=accept(s,(struct sockaddr*)&client,&l);
		printf("S-a conectat un client\n");
		if(fork()==0){
			deservire_client(c);
			exit(0);
		}

	}


	return 0;
}
