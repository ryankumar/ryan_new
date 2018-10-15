#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


typedef struct st
{
	int id[10];
  	// char id[][20];
   	char buff[1024];
   	char  ct[20];
   	char arr[10][20];
}client;


void *connect_send(void *sock_des)
{
    	int sock = *(int*)sock_des;
        int n = 0, i = 0, l = 0;

    
        char sendBuff[1024];

        bzero(sendBuff,1024);

        printf("If you want to disconnect please enter 'end'\n\n");

        printf("Enter the name and message with space\n");

        while(fgets(sendBuff, 1024 , stdin) != NULL)
        {
           	printf("sendBuff(client):%s\n",sendBuff);

              	n = send(sock,sendBuff,strlen(sendBuff),0);

              	bzero(sendBuff,1024);

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
        int n = 0, i = 0 ,l = 0 , sd = 0;

    	//    char server_message[2000];
    	//    char clientfd[10] ;
        
    	client clientfd;
    
    	bzero(clientfd.buff,1024);
    
    	memset(&clientfd,0,sizeof(clientfd));

    	while((l = recv(sock, &clientfd ,sizeof(clientfd) , 0)) > 0)
        {

                 if(l == 0)
                       printf("recv1 error\n");

                 if(l < 0)
                       perror("recv failed");
           
        
            	printf("\n\n-------------------------------------------------------\n");
                printf("Choose the name from the following:\n");
            

                for(i = 0; i < (sizeof(clientfd.id)/4) ; i++)
                {    
                        printf("client name is '%s' \n",clientfd.arr[i]);
                }

                printf("-------------------------------------------------------\n\n");

        	if((clientfd.buff[0] != '\0' ))
        	{	
              		printf("received from client '%s' :%s\n",clientfd.ct,clientfd.buff);
             		bzero(clientfd.buff,1024);
        	}        
        
         }
    
         close(sock);
    	//     pthread_detach(pthread_self());
    	//      pthread_exit(NULL);
        return 0;
}

int main()
{
        int sock_desc,*new_sock;
        struct sockaddr_in serv_addr;
        int l = 0, i = 0;
    	char name[20];

        if((sock_desc = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            	printf("Failed creating socket\n");

        bzero((char *) &serv_addr, sizeof (serv_addr));
    
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        serv_addr.sin_port = htons(1234);

        if (connect(sock_desc, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) 
        { 
            printf("Failed to connect to server\n");
            return -1;
        }

    	bzero(name, 20);

    	printf("Enter your name:");
    	scanf("%s",name);

    	send(sock_desc, name, sizeof(name), 0);



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


    	close(sock_desc);

        return 0;   
}
