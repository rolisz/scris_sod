#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char* argv[]) {

 int serv;
 struct sockaddr_in server;
 server.sin_family = AF_INET;
 server.sin_port = htons(23456);
 server.sin_addr.s_addr = inet_addr("127.0.0.1");

 serv = socket(AF_INET, SOCK_STREAM,0);

 connect(serv,(struct sockaddr*)&server,sizeof(server));
 perror("Connect \n");

 char linie[20] = "Linie spre server";
 int len = ntohs(strlen(linie));
 int loop = 0;
 while (loop++ < 5) {
    //din comoditate/lene trimitem acelasi string over and over
    send(serv,(char*)&len,sizeof(int),0);
    send(serv,linie,strlen(linie),0);
    perror("Send linie \n");

    //din motive de "Viata ii scurta", nu astept 10 secunde, ci aproximativ 3
    sleep(rand()%3 + 2);
 }
 
 close(serv);
 return 0;
}
