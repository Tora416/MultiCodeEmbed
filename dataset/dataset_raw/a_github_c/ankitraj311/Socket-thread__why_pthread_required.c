


















#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void myturn()
{
  while(1)
    {
      sleep(1);
      printf("Myturn\n");  
    }
}


void yourturn()
{
  while(1)
  {
    sleep(1);
    printf("yourturn\n");  
  }
}

int main()
{
  myturn(); 
  yourturn();   
}






















