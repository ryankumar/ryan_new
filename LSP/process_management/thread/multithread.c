// thread invokes fork()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include<string.h>
#include<signal.h>
char *msg="hiii";
sigset_t set;
int sig;
pthread_t thread,thread1,thread2;

void * fun(void * arg);
 void * fun1(void * arg);
 void * fun2(void * arg);
int main()
{
  sigemptyset(&set);
  sigaddset(&set,SIGUSR1);
  pthread_sigmask(SIG_BLOCK,&set,NULL);
  
//  pthread_t thread,thread1,thread2;
  void * t_result, * t_result1;
  pthread_create(&thread,NULL,fun,(void *)msg);
  pthread_create(&thread1,NULL,fun1,(void *)msg); // craetion of thread
  pthread_create(&thread2,NULL,fun2,(void *)msg);

  pthread_kill(thread,SIGUSR1);
  sigwait(&set,&sig);
  pthread_join(thread,&t_result);  //waiting for thread exit;
  pthread_join(thread1,&t_result1); 
  pthread_join(thread2,&t_result1);

  printf("thread is joined with return value:%s\n",(char *) t_result);

pthread_exit("EXITSTATUS");
exit(0);
}
 
void * fun(void * arg)
 {

   sigwait(&set,&sig);
  while(1){
   printf("one\n");
   pthread_kill(thread1,SIGUSR1);
   sigwait(&set,&sig);
    }
 }

  void * fun1(void * arg)
 {
  sigwait(&set,&sig);   
  while(1){
   printf("two\n");
   pthread_kill(thread2,SIGUSR1);
   sigwait(&set,&sig);
  }
 }
void * fun2(void * arg)
 {
  sigwait(&set,&sig); 
  while(1){
   printf("three\n");
   pthread_kill(thread,SIGUSR1);
   sigwait(&set,&sig);
  }
 }


