#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
int main() {
  int c;
  char s[100];

  c = socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in hints;

  hints.sin_family = AF_INET;
  hints.sin_port = htons(23456);
  hints.sin_addr.s_addr = INADDR_ANY;

  if (bind(c,(struct sockaddr*)&hints,sizeof(hints)) < 0) {
    printf("Eroare la bind \n" );
  }

  listen(c,2);
  perror("Listen");
  int i = 0;
  socklen_t m = sizeof(hints);
  int ac = accept(c,(struct sockaddr*)&hints,&m);
  if (ac < 0) {
    perror("Accept");
  }
  while (i < 3) {
    int lung;
    if (recv(ac,(char*)&lung,sizeof(int),0)<0) {
      perror("First recv");
    }
    
    lung = ntohs(lung);
    if (recv(ac,s,lung,0) <0) {
      perror("Second recv");
    }

    s[lung -1 ]  = '\0';


    char temp[100];
    int j,contor = 0;
    for (j=0;j<lung-1; j++) {
      if (!(s[j]> '0' && s[j] < '9')) {
        temp[contor] = s[j];
        contor++;
      }
    }
    temp[contor]='\0';
    printf("%s %d \n",temp,lung);
    i++;
  }

  close(c);
  return 0;
}
