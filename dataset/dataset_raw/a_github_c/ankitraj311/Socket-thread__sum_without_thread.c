#include<stdio.h>
#include<stdlib.h>
#include <time.h>
     








unsigned long addall()
{
  unsigned long sum = 0;
  int i = 0;
  while(i<=1000000000)
  {
    sum += i;
    i++;
  }
  return sum;

}

int main()
{
  clock_t start, end;
  double cpu_time_used;
  start = clock();
  unsigned long sum = 0, i =0;
  
  sum = addall();
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Sum of the numbers till 100 Crore is %lu and Time taken by Program without thread is %f",sum,cpu_time_used);
}
