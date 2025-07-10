#include<stdio.h>
#include<stdlib.h>
int main()
{
  int i=0,j=0,k=0, no=0, min_sum = 0, sum = 0, min_i = 0, min_j = 0;
  printf("Enter Length of Array");
  scanf("%d",&no);
  int array1[no];





  for(i=0; i<no; i++)
  {
    scanf("%d",&array1[i]);
  }
  min_sum = array1[0] + array1[1];
  for(i=0; i<no; i++)
  {
    printf("%d ",array1[i]);
  }
  
  for(i=0; i<no; i++)
  {
    for(j=i+1; j<no; j++)
    {
      sum = array1[i] + array1[j];
      if( abs(min_sum) > abs(sum) )
      {
        min_sum = sum;
    min_i = i;
    min_j = j;
      }  
    }
  }
 printf("Sum of %d %d Gives Nearest\n",array1[min_i],array1[min_j]); 
}
