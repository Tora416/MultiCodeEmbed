#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>









int g = 0;

void *fun_thread(void *vargs)
{
  int myid;
  myid = *(int *)vargs;
  static int s = 0;
  s++;
  g++;
  while(1)
  {
    int i = 1;
  }
  printf("Thread Id u: %d, Thread Id d: %d, Static: %d, Global: %d\n",myid,myid,++s,++g);

}


int main()
{
  int i = 0;
  pthread_t thread_id;
  for(i = 0; i<3; i++)
  {
    pthread_create(&thread_id,NULL,fun_thread,(void *)&i);
  }
  pthread_exit(NULL);
    return 0;

}
