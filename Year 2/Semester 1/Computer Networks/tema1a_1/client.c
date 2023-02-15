#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
// Un client trimite unui server un sir de numere. Serverul va returna clientului suma numerelor primite.
int main() {
  int c, nr;
  struct sockaddr_in server;
  uint16_t lg, it;
  
  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }
  
  printf("lungimea sirului de numere = ");
  scanf("%hu", &lg);
  it = lg;
  lg = htons(lg);
  send(c, &lg, sizeof(lg), 0);
  while(it--) {
	printf("un numar este = "); 
  	scanf("%hu", &nr);
  	nr = htons(nr);
  	send(c, &nr, sizeof(nr), 0); 
  }
  recv(c, &suma, sizeof(suma), 0);
  suma = ntohs(suma);
  printf("Suma este %hu\n", suma);
  close(c);
}

