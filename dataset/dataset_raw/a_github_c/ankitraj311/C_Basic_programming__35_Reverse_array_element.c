#include<stdio.h>
int main()
{
  int i=0,j=0,k=0, no=0;
  printf("Enter Length of Array");
  scanf("%d",&no);
  int array1[no], array2[no];





  for(i=0; i<no; i++)
  {
    scanf("%d",&array1[i]);
  }
  
  for(i=0; i<no; i++)
  {
    printf("%d ",array1[i]);
  }
  
  for(i=no-1; i>=0; i--)
  {
    array2[j] = array1[i];
    j++;
  }
  printf("\n");
  for(i=0; i<no; i++)
  {
    printf("%d ",array2[i]);
  }
}
