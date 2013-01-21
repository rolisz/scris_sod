#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/sysinfo.h>

int main(int argc, char* argv[]) {
  int slisten, client;
  struct sockaddr_in hints;

  slisten = socket(AF_INET,SOCK_STREAM,0);

  hints.sin_family = AF_INET;
  hints.sin_port = htons(23456);
  hints.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(slisten,(struct sockaddr*)&hints,sizeof(hints));
  perror("Bind");
  
  listen(slisten,2);
  perror("Listen");
  int loop = 0;
  while (loop++ < 3) {
      socklen_t s = sizeof(hints);
      client = accept(slisten,(struct sockaddr*)&hints,&s);
      perror("Accept");
      
      char user[100];
      recv(client,user,100,0);
      //nush ce sa fac cu el

      struct sysinfo si;

      sysinfo(&si);

      int nr = htons(si.procs);
      send(client,(char*)&nr,sizeof(int),0);

      close(client);
    
  }

  close(listen);

  return 0;
}
