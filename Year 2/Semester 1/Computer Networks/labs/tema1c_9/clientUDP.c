/*
Un client trimite unui server un nume de calculator sub forma unui sir de caractere de lungime cel mult 100. Serverul va returna clientului un numar reprezentat pe 4 octeti fara semn ce reprezinta adresa IP a calculatorului respectiv. Clientul va afisa corespunzator adresa IP (in format zecimal cu “.”) sau un mesaj de eroare daca numele calculatorului nu poate fi translatat intr-o adresa IP.
*/

#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main(int args,char** argv){

	int s,l;
	struct sockaddr_in server;
	l=sizeof(server);

	if((s=socket(AF_INET,SOCK_DGRAM,0))<0){
		printf("Eroare la creare socket\n");
		return 1;
	}
	
	memset(&server,0,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr(argv[1]);
	server.sin_port=htons(atoi(argv[2]));

	char c='a';
	sendto(s,&c,sizeof(c),0,(struct sockaddr*)&server,l);

	uint32_t rez;
	recvfrom(s,&rez,sizeof(rez),MSG_WAITALL,(struct sockaddr*)&server,&l);
	rez=ntohl(rez);
	
	printf("Am primit %d\n",rez);
	struct in_addr dummy;
	dummy.s_addr=rez;
	char* adresa_ip;
	adresa_ip=inet_ntoa(dummy);

	printf("Adresa: %s\n",adresa_ip);

	return 0;
}
