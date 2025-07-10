#include<stdio.h>
int main()
{

  int no,i,j,k,x,y,sum = 0,a,b;
  printf("Enter the Range with lower and uppar limit to find out the Happy no.  or not");
  scanf("%d%d",&a,&b);



  for(i=a; i<=b; i++)
  {
    while( i > 0 )
    {
      x = i % 10;
      sum = sum + (x*x);
      i = i / 10;
      if( i == 0)
      {
    sleep(1);
        printf("sum is %d\n",sum);
        if( sum == 1)
        {
          printf("Number is Happy");
          break;
        }
        i = sum;
        sum = 0;
      }
    }
 }
}
