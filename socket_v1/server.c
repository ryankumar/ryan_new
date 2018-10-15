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
   char  ct[1024];
   char arr[10][20];
}client;

int main(int argc , char *argv[])
{
    	int socket_desc , c , *new_sock, client_sock;
        struct sockaddr_in server , client_addr;
    
        int i = 0 , fd , fd1;
    	char name[20];


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
	//    int s = 0;
        while(1)
        {
               	client_sock = accept(socket_desc,(struct sockaddr*)&client_addr,(socklen_t*)&c);           
    
               	puts("Connection accepted");
    
               	printf("\n\n");
        
        	recv(client_sock, name, sizeof(name), 0);
        
        	write(fd1, &client_sock, sizeof(client_sock));

        	write(fd1, &name, sizeof(name));
        
    
    	}
            //pthread_join(sniffer_thread[0],NULL);
             
         return 0;
}

void *connection_recv(void *socket_desc)
{

        //Get the socket descriptor
        int sock = *(int*)socket_desc;
    
        int n = 0,fd = 0,i =0,m = 0, count = 0,cfd = 0,b = 0, c = 0;

        char client_message[1024];

    	char clnt[20] = {0};

    	client clientfd;

        int sd = 0 ,sd1 = 0, res = 0, res1 = 0 , k = 0, l = 0 ,j = 0, s =0, t = 0;

    	bzero(clientfd.buff,1024);
        char *tmp_buff;
    	char sum[20] = {0};
   
        fd_set readfds;

        while(1)
        {
                FD_ZERO(&readfds);
               
                FD_SET(sock,&readfds);
	
                for(i =  0; i < count ; i++)
                {
                    	FD_SET(clientfd.id[i], &readfds);
            		printf("clientfd[i]:%d\n",clientfd.id[i]);
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
                                read(sock , &cfd, sizeof(cfd));

                		read(sock, &clnt, sizeof(clnt));
                
                		printf("cfd:%d\n",cfd);
                
                		printf("name:%s\n",clnt);

                             	clientfd.id[count] = cfd;
        
                		strcpy(clientfd.arr[t],clnt);

                             	count++;

                		t++;
                
                        
                		for(i = 0 ; i < count ; i++)
                        	{    
                                	send(clientfd.id[i], &clientfd, sizeof(clientfd), 0);    
                        		//        printf("Clientfd:%d\n",clientfd.id[i]);
                        		bzero(clientfd.buff,1024);
                        	}
            

                    		printf("\n\n-------------------------------------------------------\n");
                                printf("Choose the client from the following:\n");

                                for(i = 0;i < count;i++)
                                {
                                        printf("client name is %s\n",clientfd.arr[i]);
                                }

                                printf("-------------------------------------------------------\n\n");
            		}
              
                    	for(i = 0; i < count ; i++)
                        { 
                		printf("count : %d\n",count);

                        	sd1 = clientfd.id[i] ;

                                printf("sd1:%d\n",sd1);


                                if (FD_ISSET(sd1, &readfds))
                                {        
                    			printf("fdset\n");
                    			bzero(clientfd.buff, 1024);

                    			bzero(client_message, 1024);

                
                    			n = recv(sd1, client_message, 1024, 0);

                                	printf("client:%s\n",client_message);
                    			for(b = 0; b < count ; b++)
                    			{
                        			printf("In loop:%d\n",count);
                        			if(sd1 == clientfd.id[b])
                            			break;
                    
                    			}
                    
                    			strcpy(clientfd.ct, clientfd.arr[b]);
                    
                                
                                        for(k = 0; client_message[k] != ' '; k++)
                                        {
                                                sum[k] = client_message[k];
                                        }
                                        
                    			printf("client name:%s\n",sum);
                         
                                        for(c = 0; c < count ; c++)
                                        {
                                                res = strcmp(sum,clientfd.arr[c]);
                        			if(res == 0)
                                                break;
                                        }
                    			sd = clientfd.id[c];
                    
                    			strcpy(clientfd.buff, &client_message[k+1]);

                                	res1 = strcmp(clientfd.buff, "end\n");

                                  	if((n == 0) ||  (res1 == 0))
                                        {
                                               printf("Client Disconnected : %d\n",sd1);
                                                                         
                           			int temp = 0 , j = i;

                                               	count = count-1;

                                                while(j <= count)
                                                {
                        				//    printf("(In loop )count : %d\n",count);
                                                        temp = clientfd.id[j];
                                                        
                            				clientfd.id[j] = clientfd.id[j+1];
                                                        
                            				clientfd.id[j+1] = temp;
                                                        
                            				j++;
                                                }

                                                close(sd1);
                        
                        			bzero(clientfd.buff,1024);

                                                //printf("%d\n",count);
                                                clientfd.id[j] = 0;

                        			for(i = 0 ; i < count ; i++)
                                                {
                                                        send(clientfd.id[i], &clientfd, sizeof(clientfd), 0);

                                                        bzero(clientfd.buff,1024);
                                                }

                              		}
    
                                	else if(n < 0)
                                            perror("recv failed");

                                    	else
                                	{                           
                                    		if((sd != -1) && (clientfd.buff[0] != '\0' ) && (sd != sd1))
                                        	{
                                                	for(i =0 ;i < count; i++)
                                                	{
                                                        	if(sd == clientfd.id[i])
                                                        	{    
                                                    			l = send(sd, &clientfd, sizeof(clientfd), 0);                                
                                     					bzero(clientfd.buff, 1024);
                                                     		}    
                                            		}

                                    		}
                        			/*else
                        			{
                            			strcpy(clientfd.buff,"You are trying to communicate with your own client,give another descriptor");
                            				send(sd, &clientfd, sizeof(clientfd), 0);
                             				bzero(clientfd.buff, 1024);
                        			}*/


                                
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

