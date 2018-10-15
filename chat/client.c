#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <pthread.h>
#include<sys/types.h>

void * cientThread(void *arg)
{
  printf("In thread\n");
  char message[1000];
  char buffer[1024];
  int clientSocket;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  char addr[]="127.0.0.1";

  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  serverAddr.sin_family = AF_INET;

  serverAddr.sin_port = htons(1234);

// serverAddr.sin_addr.s_addr = inet_pton("localhost");
  int in = inet_pton(AF_INET,addr , &serverAddr.sin_addr);
   if(in<0)
   {
     perror("client Error: IP not created: ");
     return 0;
   }
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    addr_size = sizeof serverAddr;

    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

    strcpy(message,"Hello");

   if( send(clientSocket , message , strlen(message) , 0) < 0)
    {
            printf("Send failed\n");
    }

    if(recv(clientSocket, buffer, 1024, 0) < 0)
    {
       printf("Receive failed\n");
    }

    printf("Data received: %s\n",buffer);
    close(clientSocket);
    pthread_exit(NULL);
}
int main(){

  int i = 0;
  pthread_t tid[51];

  while(i< 10)
  {
    if( pthread_create(&tid[i], NULL, cientThread, NULL) != 0 )
           printf("Failed to create thread\n");
    i++;
  }
  sleep(20);
  i = 0;
  while(i< 10)
  {
     pthread_join(tid[i++],NULL);
     printf("%d:\n",i);
  }
  return 0;
}


