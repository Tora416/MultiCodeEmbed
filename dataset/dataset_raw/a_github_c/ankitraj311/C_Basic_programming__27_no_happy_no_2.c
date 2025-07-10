#include<stdio.h>
int main()
{
  int i,j,k,x,y,no,sum=0;
  printf("Enter the number to find out happy or not");
  scanf("%d",&no);







  while( sum != 1)
  {
    sum = 0;
    while(no>0)
    {
      i = no % 10;
      sum = sum + (i*i);
      no = no / 10;
    }
    no = sum ;
    printf("sum is %d", sum);
  }

  if( sum == 1)
  {
    printf("Happy number");
  }
  else
  {
    printf("Not Happy number");
  }
}
