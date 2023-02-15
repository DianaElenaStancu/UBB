/*
Un client trimite unui server un sir de caractere. Serverul va returna clientului acest sir oglindit (caracterele sirului in ordine inversa).
*/

#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

void oglindit(char sir[101]){
	for(int i=0;i<strlen(sir)/2;i++){
		char aux=sir[i];
		sir[i]=sir[strlen(sir)-1-i];
		sir[strlen(sir)-1-i]=aux;
	}
}

//se va returna dimensiunea
uint16_t citire_sir(int c,char sir[101]){
	uint16_t dimensiune;
	recv(c,&dimensiune,sizeof(dimensiune),MSG_WAITALL);
	dimensiune=ntohs(dimensiune);

	// + 1 - se citeste si terminatorul
	for(int i=0;i<dimensiune+1;i++){
		recv(c,&sir[i],sizeof(sir[i]),MSG_WAITALL);
	}
	return dimensiune;
}

void trimitere_sir(int c,char sir[101]){
	for(int i=0;i<strlen(sir)+1;i++){
		send(c,&sir[i],sizeof(sir[i]),0);
	}
}

void deservire_client(int c){

	char sir[101];
	uint16_t dim=citire_sir(c,sir);
	oglindit(sir);
	trimitere_sir(c,sir);
	close(c);
}

int main(){

	int s,c,l;
	struct sockaddr_in server,client;
	l=sizeof(client);

	if((s=socket(AF_INET,SOCK_STREAM,0))<0){
		printf("Ëroare la creare socket\n");
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
		c=accept(s,(struct sockaddr*)&client,&l);
		printf("S-a conectat un client\n");
		if(fork()==0){
			deservire_client(c);
			exit(0);
		}
	}

	return 0;
}
