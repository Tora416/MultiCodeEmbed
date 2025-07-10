#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>







int g = 0;
void* thread_fun(void *vargp)
{ 
  
  
  int myid = *(int *)vargp;

  
  static int s = 0;
  
  ++s;
  ++g;
   while(1)
   {
     int i = 1;
   }
  
  printf("Thread Id u: %d, Thread Id d: %d, Static: %d, Global: %d\n",myid,myid,++s,++g);
}


int main()
{
  int  i;
  pthread_t tid;

  
  for(i = 0; i<3; i++)
  {
    
    pthread_create(&tid, NULL, thread_fun, (void*)&i);
  }
    
    pthread_exit(NULL);
    return 0;
}
