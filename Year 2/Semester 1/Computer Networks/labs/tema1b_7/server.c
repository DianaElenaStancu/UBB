/*
Un client trimite unui server un sir de caractere si doua numere (fie acestea s, i, l). Serverul va returna clientului subsirul de lungime l a lui s care incepe la pozitia i.
*/

#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define DIM 101

void citire_sir(int c,char sir[DIM]){
	uint16_t dimensiune;
	recv(c,&dimensiune,sizeof(dimensiune),MSG_WAITALL);
	dimensiune=ntohs(dimensiune);

	for(int i=0;i<dimensiune+1;i++){
		recv(c,&sir[i],sizeof(sir[i]),MSG_WAITALL);
	}
}

void deservire_client(int c){
	//se primeste mai intai sirul
	char sir[DIM];
	citire_sir(c,sir);	

	uint16_t i,l;
	recv(c,&i,sizeof(i),MSG_WAITALL);
	recv(c,&l,sizeof(l),MSG_WAITALL);
	i=ntohs(i);  l=ntohs(l);

	uint16_t dimensiune=0;

	//subsirul
	if(strlen(sir)-1<l+1){ //nu putem gasi un subsir
		char x='\0';
		dimensiune=htons(dimensiune); //0
		send(c,&dimensiune,sizeof(dimensiune),0);
		send(c,&x,sizeof(x),0);
		return;
	}

	dimensiune=l;
	dimensiune=htons(dimensiune);
	send(c,&dimensiune,sizeof(dimensiune),0);

	for(dimensiune=0;dimensiune<l;dimensiune++){
		send(c,&sir[i+dimensiune],sizeof(sir[i+dimensiune]),0);
	}

	close(c);
}

int main(){

	int s,c;
	struct sockaddr_in server,client;
	int lung=sizeof(client);

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
		printf("Astept clienti....\n");
		c=accept(s,(struct sockaddr*)&client,&lung);
		printf("S-a conectat un client\n");
	
		if(fork()==0){
			deservire_client(c);
			exit(0);
		}
	}

	close(s);
	return 0;
}
