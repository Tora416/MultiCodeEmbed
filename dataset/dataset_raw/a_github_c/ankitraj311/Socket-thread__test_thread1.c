#include<stdio.h>
#include<stdlib.h> 
#include<pthread.h> 
#include<unistd.h> 









void* fun_call()
{
  sleep(1);
  printf("First Thread is created\n");
  
}


int main()
{
  pthread_t thread_id;
  printf("Befor Execution of Thread\n");
  pthread_create(&thread_id,NULL,fun_call,NULL);
  printf("Thread_id is %lu\n",thread_id);
  pthread_join(thread_id,NULL);
  printf("after Execution of Thread\n");
}

