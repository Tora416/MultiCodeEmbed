#include<stdio.h>
int main()
{
  int i,j,k,array1[100],array2[100],no=0, min = 0, max = 0;
  printf("Enter number of Digit you want to use in Array\n");
  scanf("%d",&no);  





  for(i=0; i<no; i++)
  {
    scanf("%d",&array1[i]);
  }
  
  for(i=0; i<no; i++)
  {
    printf("%d ",array1[i]);
  }
 
  min = array1[0];
  max = array1[0];

  printf("Min Value Befor is %d\n",min);
  printf("Max Value Befor is %d\n",max);
  for(i=1; i<no; i++)
  {
    if(min > array1[i])
    {
      min = array1[i];    
    }
    
    if(max < array1[i])
    {
      max = array1[i];    
    }
  }
  printf("Min Value After is %d\n",min);
  printf("Max Value After is %d\n",max);
}
