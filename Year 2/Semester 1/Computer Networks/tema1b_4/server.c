/*
Un client trimite unui server doua siruri de caractere ordonate. Serverul va interclasa cele doua siruri si va returna clientului sirul rezultat interclasat.
*/

#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#define DIM 101

void interclasare(char sir1[DIM],char sir2[DIM],char sir_rez[DIM*2]){

	int i=0,j=0,k=0;
	while(i<strlen(sir1) && j<strlen(sir2)){
		if(sir1[i] < sir2[j]){
			sir_rez[k++]=sir1[i];
			i++;
		}
		else{
			sir_rez[k++]=sir2[j];
			j++;
		}
	}

	while(i<strlen(sir1)){
		sir_rez[k++]=sir1[i];
		i++;
	}

	while(j<strlen(sir2)){
		sir_rez[k++]=sir2[j];
		j++;
	}
	sir_rez[k]='\0';
}

void citire_sir(int c,char sir[DIM]){
	uint16_t lungime;
	recv(c,&lungime,sizeof(lungime),MSG_WAITALL);
	lungime=ntohs(lungime);
	printf("Dimensiune = %hu\n",lungime);

	for(int i=0;i<lungime+1;i++){
		recv(c,&sir[i],sizeof(sir[i]),MSG_WAITALL);
	}
}

void trimite_sir(int c,char sir[DIM*2]){
	uint16_t lungime=strlen(sir);
	lungime=htons(lungime);
	send(c,&lungime,sizeof(lungime),0);
	for(int i=0;i<strlen(sir)+1;i++){
		send(c,&sir[i],sizeof(sir[i]),0);
	}
}

void deservire_client(int c){
	char sir1[DIM],sir2[DIM],sir_rez[DIM*2];
	citire_sir(c,sir1);
	citire_sir(c,sir2);
	interclasare(sir1,sir2,sir_rez);
	trimite_sir(c,sir_rez);
	close(c);	
}

int main(){

	int s,c,l;
	struct sockaddr_in server,client;

	if((s=socket(AF_INET,SOCK_STREAM,0))<0){
		printf("Eroare la creare socket\n");
		return 1;
	}

	memset(&server,0,sizeof(server));
	memset(&client,0,sizeof(client));
	l=sizeof(client);

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
