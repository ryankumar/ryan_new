#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_SIZE 50

 typedef struct client{
	int id[10];
	char buff[1024];
 }client;


void *connect_send(void *sock_des)
{
	int sock = *(int*)sock_des;
    	int n = 0, i = 0, l = 0;

    
     	char sendBuff[100];

     	bzero(sendBuff,MAX_SIZE);

     	printf("If you want to disconnect please enter 'end'\n");

     	printf("Enter the client descriptor and message with space\n");

     	while(fgets(sendBuff, 100 , stdin) != NULL)
     	{
        	printf("sendBuff(client):%s\n",sendBuff);

          	n = send(sock,sendBuff,strlen(sendBuff),0);

          	bzero(sendBuff,MAX_SIZE);

         	//printf ("Send Returns : %ld\n", send(sock,sendBuff,n,0));
        	//if(n == 0)
         	//printf("You have been disconnected with server\n");

          	if(n < 0)
          	perror("send failed , you have been disconnected with client");

       	}

       	close(sock);
    	//  pthread_exit(NULL);
    	//  pthread_detach(pthread_self());
      	return 0;
}

void *connect_recv(void *sock_des)
{
    	int sock = *(int*)sock_des;
    	int n = 0, i = 0 ,l = 0;

    //	char server_message[2000];
    //	char clientfd[10] ;
    	client clientfd;
	bzero(clientfd.buff,1024);

	while((l = recv(sock, &clientfd ,sizeof(clientfd) , 0)) > 0)
    	{
             	if(l == 0)
                       printf("recv1 error\n");

             	if(l < 0)
                       perror("recv failed");
   		
		printf("\n\n-------------------------------------------------------\n");
         	printf("Choose the descriptor from the following descriptors:\n");


         	for(i = 0; i < (sizeof(clientfd.id)/4) ; i++)
         	{
			if(clientfd.id[i]>0)	
                	printf("client %d desriptor is '%d' \n",i,clientfd.id[i]);
         	}
         	//printf("strlen:%lu\n",strlen(clientfd));

         	printf("-------------------------------------------------------\n\n");
         	printf("Now Please enter the client descriptor and then message:\n");
		
	 	 printf("received(client):%s\n",clientfd.buff);
		 bzero(clientfd.buff,1024);
     	}
    
     	close(sock);
	//     pthread_detach(pthread_self());
	//        pthread_exit(NULL);
    	return 0;
}

int main()
{
    	int sock_desc,*new_sock;
    	struct sockaddr_in serv_addr;
    	int l = 0, i = 0;

    	if((sock_desc = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        	printf("Failed creating socket\n");

    	bzero((char *) &serv_addr, sizeof (serv_addr));

    	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_addr.s_addr = inet_addr("192.168.1.10");
    	serv_addr.sin_port = htons(1234);

    	if (connect(sock_desc, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) 
    	{
        	printf("Failed to connect to server\n");
        	return -1;
    	}

  	//  printf("client side(sock desc):%d\n",sock_desc);

    	printf("Connected successfully\n");

    	pthread_t thread[2];
    	new_sock = malloc(sizeof(*new_sock));
    	*new_sock = sock_desc;

    	//printf("client side(new sock):%d\n",*new_sock);

    	if( (pthread_create(&thread[0], NULL,connect_send,(void*)new_sock)) != 0 )
           	printf("client : Failed to create thread\n");

    	if( pthread_create(&thread[1], NULL,connect_recv,(void*)new_sock) != 0 )
           printf("client : Failed to create thread\n");    
    
    	pthread_join(thread[0],NULL);
    	pthread_join(thread[1],NULL);    


	//    close(sock_desc);
    	return 0;   
}
