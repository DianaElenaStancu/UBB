/*
Un client trimite unui server un nume de calculator sub forma unui sir de caractere de lungime cel mult 100. Serverul va returna clientului un numar reprezentat pe 4 octeti fara semn ce reprezinta adresa IP a calculatorului respectiv. Clientul va afisa corespunzator adresa IP (in format zecimal cu “.”) sau un mesaj de eroare daca numele calculatorului nu poate fi translatat intr-o adresa IP.
*/

#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#define DIM 101

uint32_t convert(char* adresa){

	char delim[]=".";
	uint32_t rez=0;
	char* numar=strtok(adresa,delim);
	int putere=24;
	
	printf("Aici\n");

	while(numar!=NULL){
		int nr = atoi(numar);
		rez+=nr<<putere;
		putere-=8;
		numar=strtok(NULL,delim);
	}

	printf("Se termina\n");
	return rez;
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
	memset(&client,0,sizeof(client));
	server.sin_addr.s_addr=inet_addr("0.0.0.0");
	server.sin_family=AF_INET;
	server.sin_port=htons(1234);

	if(bind(s,(struct sockaddr*)&server,sizeof(server))<0){
		printf("Eroare la bind\n");
		return 1;
	}

	while(1){
		printf("Astept clienti...\n");
		//clientul trimite un caracter
		char c;	
		recvfrom(s,&c,sizeof(c),MSG_WAITALL,(struct sockaddr*)&client,&l);
		
		char ip[INET_ADDRSTRLEN];
		struct sockaddr_in* adresa=&client;
		struct in_addr adresa_ip=adresa->sin_addr;
		inet_ntop(AF_INET,&adresa_ip,ip,INET_ADDRSTRLEN);
		printf("Clientul are adresa: %s\n",ip);

//		uint32_t rez=convert(ip);
		uint32_t rez=client.sin_addr.s_addr;
		printf("Rez = %d\n",rez);
		rez=htonl(rez);
		sendto(s,&rez,sizeof(rez),0,(struct sockaddr*)&client,l);

	}
	close(s);

	return 0;
}
