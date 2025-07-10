#include<stdio.h>
int main()
{
  int i,j,k,x,y,no,sum=0,a,b,dummy1=0, dummy2 = 0;
  printf("Enter the Range to find the Perfect number between them");
  scanf("%d%d",&a,&b);





  for(j=a; j<=b; j++)
  {
    sum = 0;
    dummy1 = j;
    for( i=1; i<j; i++)
    {
      if(dummy1 % i == 0)
      {
        sum = sum + i;
      }
    }
    if( dummy1 == sum)
    {
      printf("%d ",dummy1);
    }
  }

}

