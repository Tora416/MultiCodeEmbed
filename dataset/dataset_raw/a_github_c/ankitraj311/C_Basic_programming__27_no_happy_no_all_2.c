#include<stdio.h>
int main()
{
  int i,j,k,x,y,no,sum=0,dummy1=0;
  printf("Enter the number to find out happy or not");
  







  for(j=1; j<=1000; j++)
  {
    sum = 0;
    dummy1 = j;
    while( sum != 1 && sum != 4 )
    {
      sum = 0;
      while(dummy1>0)
      {
        i = dummy1 % 10;
        sum = sum + (i*i);
        dummy1 = dummy1 / 10;
      }
      dummy1 = sum ;
    }
 
    if( sum == 1)
    {
      printf("%d ",j);
    }
  }
}
