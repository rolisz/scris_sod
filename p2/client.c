#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
int main() {
   char s[100];

   int sock = socket(AF_INET,SOCK_STREAM,0);

   struct sockaddr_in server;

   server.sin_port = htons(23456);
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = inet_addr("127.0.0.1");

   if (connect(sock,(struct sockaddr*)&server,sizeof(server)) < 0) {
      printf("Eroare la connect \n");
      return 1;
   }
   

   int i = 0;
   while (i < 3) {
      fgets(s,100,stdin);
      
      printf("%s %d \n",s,strlen(s));
      int l = htons(strlen(s));
      send(sock,(char*)&l,sizeof(int),0);
      send(sock,s,strlen(s),0);
      int sl = rand() % 3;
      printf("Sleeping for %d seconds \n",sl);

      sleep(sl);
      i++;
   }
}
