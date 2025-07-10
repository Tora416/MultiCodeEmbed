#include<stdio.h>
int main()
{
  int i,j,k,x,y,no,count=0;
  printf("Enter the number, upto which you want to find out prime or not");
  scanf("%d",&no);
  







  for(j=1; j<=no; j++)
  {
      count = 0;
      for(i=1; i<=j; i++)
      {
        if( j%i == 0)
        {
          count++;
        }
      }
      if( count == 2)
      {
        printf("%d \n",j);
      }
  }
}


