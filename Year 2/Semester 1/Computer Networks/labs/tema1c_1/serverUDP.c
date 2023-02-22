#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
 
int main() {
  int s;
  struct sockaddr_in server, client;
  int l;
  
  s = socket(AF_INET, SOCK_DGRAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  
  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }
 
  l = sizeof(client);
  memset(&client, 0, sizeof(client));
  
  while (1) {
	printf("Astept...");
	uint16_t a, b, suma;
        recvfrom(s, &a, sizeof(a), MSG_WAITALL, (struct sockaddr*)&client, (socklen_t *)&l);
	recvfrom(s, &b, sizeof(b), MSG_WAITALL, (struct sockaddr*)&client,(socklen_t *)&l);
  	a = ntohs(a);
        b = ntohs(b);
	printf("Am primit de la client a = %hu si b = %hu", a, b);
	suma = a + b;
	suma = htons(suma);
 	sendto(s,&suma,sizeof(suma),0,(struct sockaddr*)&client,l);
  } 
  close(s);
}
