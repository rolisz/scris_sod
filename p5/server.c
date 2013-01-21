#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/sysinfo.h>
#include <time.h>

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
  socklen_t s = sizeof(hints);
  client = accept(slisten,(struct sockaddr*)&hints,&s);
  perror("Accept");
  int timp = time(NULL);
  //pentru ca mi lene, nu mai fac cate un thread
  while (loop++ < 5) {
      
      char linie[100];
      int lungime;
      recv(client,(char*)&lungime,sizeof(int),0);
      perror("Lungime \n");
      recv(client,linie,ntohs(lungime),0);
      perror("Linie \n");

      int dif = timp - time(NULL);
      if (dif == -3) {
        printf("La timp %s \n",linie);
      }
      else {
        printf("A venit cu o diferenta de %d mesajul %s \n",dif,linie);
      }
      timp = time(NULL);

  }
  close(client);
  close(listen);

  return 0;
}
