#include<stdio.h>
int main()
{
  int i=0,j=0,k=0,array[100]={0}, no = 0,latest_no = 0, last = 0, sum = 0;
  printf("Enter Length of Array");
  scanf("%d",&no);





  for(i=0; i<no; i++)
  {
    scanf("%d",&array[i]);
  }
  
  for(i=0; i<no; i++)
  {
    latest_no = array[i];
    sum = 0;
    while(latest_no != 0)
    {
      last = latest_no%10;
      sum = (sum*10) + last;
      latest_no = latest_no/10;
    }
    printf("value of Sum is %d\n",sum);
    if( array[i] == sum)
    {
      printf("%d is Palindrom\n\n",sum);
    }
    else
    {
      printf("No Number is Palindrom\n\n");
    }
  }



}
