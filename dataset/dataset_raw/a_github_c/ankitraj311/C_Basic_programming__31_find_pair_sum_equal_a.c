#include<stdio.h>
int main()
{
  int i=0,j=0,k=0,array[100]={0},array2[100] = {0}, no=0,insert_no=0,insert_index=0,flag=0,pair_sum = 0;
  printf("Enter Length of Array");
  scanf("%d",&no);





  for(i=0; i<no; i++)
  {
    scanf("%d",&array[i]);
  }
  for(i=0; i<no; i++)
  {
    printf("%d ",array[i]);
  }
  
  printf("\nEnter Element, whose you want to find pair");
  scanf("%d",&pair_sum);
  printf("\nPair_sum is %d\n",pair_sum);

  for(i=0; i<no; i++)
  {
    for(j=i+1; j<no; j++)
    {
     if(array[i] + array[j] == pair_sum)
     {
       printf("Pair for %d are (%d,%d) found at (%d,%d) position\n",pair_sum,array[i],array[j],i,j);
     }
    }
  }

}
