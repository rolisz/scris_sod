#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("Dati parametrul user");
    exit(1);
  }

 int serv;
 struct sockaddr_in server;
 server.sin_family = AF_INET;
 server.sin_port = htons(23456);
 server.sin_addr.s_addr = inet_addr("127.0.0.1");

 serv = socket(AF_INET, SOCK_STREAM,0);

 connect(serv,(struct sockaddr*)&server,sizeof(server));
 perror("Connect \n");

 send(serv,argv[1],sizeof(argv[1]),0);
 perror("Send user \n");

 int nr;
 recv(serv,(char*)&nr,sizeof(int),0);
 perror("Receive number \n");

 nr = ntohs(nr);

 printf("Sunt %d procese \n",nr);
 close(serv);
 return 0;
}
