#include<stdio.h>
int main()
{
  int i,j,k,array[100],no=0, neg_sum = 0, pos_sum = 0;
  printf("Enter How many numbers you want to Enter");
  scanf("%d",&no);
  
  
  
  
  
  for(i=0; i<no; i++)
  {
    scanf("%d",&array[i]);
  }

  for(i=0; i<no; i++)
  {
    printf("%d ",array[i]);
  }

  for(i=0; i<no; i++)
  {
    if( array[i] < 0)
    {
      neg_sum = neg_sum - (-array[i]);
    }
    if( array[i] > 0)
    {
     pos_sum = pos_sum + (array[i]);
    }
  }

  printf("Neg_Sum is %d Pos_Sum is %d",neg_sum,pos_sum);
}
