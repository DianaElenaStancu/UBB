#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
// 5. Un client trimite unui server un numar. Serverul va returna clientului sirul divizorilor acestui numar.
int main() {
  int c, re;
  struct sockaddr_in server;
  uint16_t a, div;
  
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
  
  printf("a = ");
  scanf("%hu", &a);
  a = htons(a);
  send(c, &a, sizeof(a), 0);
  while(1) { 
 	re = recv(c, &div, sizeof(div), MSG_WAITALL);
	if (re <= 0) 
		break;
	div = ntohs(div);
  	printf("Un divizor este %hu\n", div);
  }
  close(c);
}
