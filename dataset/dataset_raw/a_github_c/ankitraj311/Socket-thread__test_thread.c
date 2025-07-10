#include<stdio.h>
#include<pthread.h>










void *thread_fun(void *id)
{
  int *new_thread = (int *)id;
  printf("new_thread id is %d\n",*new_thread);

}



int main()
{
  pthread_t id;

  for(int i = 0; i<3; i++)
  {
    pthread_create(&id, NULL, thread_fun, (void *)&id);
  }
  pthread_join(id,NULL);

  pthread_exit(NULL);
}
