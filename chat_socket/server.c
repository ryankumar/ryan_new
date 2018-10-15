#include <stdio.h>
#include <stdlib.h>    
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>    
#include <pthread.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void *connection_recv(void *);
typedef struct st
{
   int id[10];
   char buff[1024];
}client;

#define MAX_SIZE 50

int main(int argc , char *argv[])
{
	int socket_desc , c , *new_sock, client_sock;
    	struct sockaddr_in server , client;
    
    	int i = 0 , fd , fd1;

    	//Create socket
    	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    	if (socket_desc == -1)
    	{
        	printf("Could not create socket");
    	}
    	puts("Socket created");

    	//Prepare the sockaddr_in structure
    	server.sin_family = AF_INET;
    	server.sin_addr.s_addr = INADDR_ANY;
    	server.sin_port = htons(1234);

    	int tr = 1;
   
    	// kill Address already in use error message

    	if (setsockopt(socket_desc,SOL_SOCKET,SO_REUSEADDR,&tr,sizeof(int)) == -1) {
    		perror("setsockopt");
    		exit(1);
    	}

    	//Bind
    	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    	{
      		printf("bind failed\n");
        	//print the error message
       		// perror("bind failed. Error");
        	return 1;
    	}
 
    	puts("bind done");

    	//Listen
    	listen(socket_desc ,10);

    	//Accept and incoming connection
    	puts("Waiting for incoming connections...");
    
    	c = sizeof(struct sockaddr_in);

    	// FIFO file path
    	char *myfifo = "myfifoo" , *myfifo1 = "myfifo1";


    	mkfifo("myfifo1", 0666);

    	fd1 = open("myfifo1", O_RDWR);

    	pthread_t sniffer_thread[1];


        if(pthread_create(&sniffer_thread[0] , NULL, connection_recv,&fd1) < 0)
        {
                perror("could not create thread2");
                return 1;
        }

       	while(1)
       	{
           	client_sock = accept(socket_desc,(struct sockaddr*)&client,(socklen_t*)&c);           
    
           	puts("Connection accepted");
    
           	printf("\n\n");

           	write(fd1, &client_sock, sizeof(client_sock));

    		//printf("%d:IP address is: %s\n",i,inet_ntoa(client.sin_addr));
    		//printf("port is: %d\n", (int) ntohs(client_addr.sin_port));

    		//printf("Server side(sock desc):%d , pipe fd:%d\n",client_sock,fd);
    
    		//pthread_join(sniffer_thread[0],NULL);
    		//pthread_join(sniffer_thread[1],NULL); 

       	}
     	return 0;
}

void *connection_recv(void *socket_desc)
{

    	//Get the socket descriptor
    	int sock = *(int*)socket_desc;
    
    	int n = 0,fd = 0,i =0,m = 0, count = 0,cfd;

    	char client_message[2000];

    //	char clientfd[10] = {0};
	client clientfd;
    	int sd = 0 , res = 0, res1 = 0 , k = 0, l = 0;
	bzero(clientfd.buff,1024);
    	char *tmp_buff;
   
    	fd_set readfds;

        while(1)
        {
                FD_ZERO(&readfds);
               
               	FD_SET(sock,&readfds);

                for(i =  0; i < count ; i++)
                {
                    FD_SET(clientfd.id[i], &readfds);
                }

                fd = select(FD_SETSIZE, &readfds, NULL, NULL, NULL);

                if (fd < 0)
                {
                    	perror("select failed");
                    	exit(-1);
                }
        
        	if(fd > 0)
                {
                	if(FD_ISSET(sock, &readfds))
                        {
                                read(sock , &cfd , sizeof(cfd));
                     		clientfd.id[count] = cfd;
                     		count++;
                        }
            
                        printf("\n\n-------------------------------------------------------\n");
                        printf("Choose the descriptor from the following descriptors:\n");

                        for(i = 0; i < count;i++)
                        {
                        	printf("client %d desriptor is  '%d'  \n",i,clientfd.id[i]);
                        }
                
                        printf("-------------------------------------------------------\n\n");
                        printf("Now Please enter the client descriptor and then message:\n");    

                        //printf("strlen(clientfd):%lu\n",strlen(clientfd));        
            
            		for(i = 0 ; i < count ; i++)
            		{
                		send(clientfd.id[i], &clientfd, sizeof(clientfd), 0);    
                		//printf("Clientfd:%d\n",clientfd[i]);
				bzero(clientfd.buff,1024);
            		}
            
              
            		for(i = 0; i<count ; i++)
                        {
                		sd = clientfd.id[i] ;
                
                                if (FD_ISSET(sd, &readfds))
                                {
                                    	n = recv(sd,client_message,2000,0);

                                	//    printf("received from client descriptor (%d) : %s\n",sd,client_message);
                    
                    			int sum = 0;

                                        for(k = 0; client_message[k] != ' ';k++)
                                        {
                                                sum = sum * 10 + client_message[k] - 48 ;
                                        	//      printf("sum :%d\n",sum);
                                        }
                                        sd = sum;

                                       // clientfd.buff = &client_message[k+1];
					strcpy(clientfd.buff,&client_message[k+1]);


                    			res1 = strcmp(clientfd.buff,"end\n");

                      			if((n == 0) ||  (res1 == 0))
                                        {
                                               printf("Client Disconnected : %d\n",sd);
                                 
                                                int temp = 0 , j = i;

                                                count = count-1;

                                                while(j <= count)
                                                {
                                                        temp = clientfd.id[j];
                                                        clientfd.id[j] = clientfd.id[j+1];
                                                        clientfd.id[j+1] = temp;
                                                        j++;
                                                }
                            
                                                close(sd);
                                                //printf("%d\n",count);
                                                clientfd.id[j] = 0;
                    			} 
                    			else if(n < 0)
                                        	perror("recv failed");

                                	else
                    			{                    
                        			if((sd != -1) && (clientfd.buff[0] != '\0' ))
                                		{
                                        		for(i =0 ;i < count;i++)
                                        		{
                                                		if(sd == clientfd.id[i])
                                                		{	

                                					l = send(sd,&clientfd,sizeof(clientfd),0);                                
                                                        		res = strcmp(clientfd.buff,"end\n");

                                                         		printf("msg:%s\n",clientfd.buff);

                                                            		if((l == 0) || (res == 0)) 
                                                         		{
                                                                    		printf("Client Disconnected : %d\n",sd);
        
                                                                     		int temp = 0 , j = i;

                                                                     		count = count - 1;
                                                        
                                                                       		while(j <= count)
                                    						{
                                                                            		//printf("j:%d\n",j);
                                                                            		temp = clientfd.id[j];
                                                                        		clientfd.id[j] = clientfd.id[j+1];
                                                                        		clientfd.id[j+1] = temp;
                                                                        		j++;
                                                                 		}
                                                            			close(sd);
                                						clientfd.id[j] = 0;
										

                                 					}
								 	bzero(clientfd.buff,1024);
                                         			}	
                                			}
                        			}
                 
                    			}
            			}
        		}
    		}
	}
    	close(sock);

    	pthread_exit(NULL);
        pthread_detach(pthread_self());
    	return 0;
}
