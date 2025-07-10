#include<stdio.h>
int main()
{
  int i,j,k,no,array1[100],array2[100],max1=0,max2=0,count=0;
  printf("Enter Length of Array\n");
  scanf("%d",&no);






  for(i=0; i<no; i++)
  {
    scanf("%d",&array1[i]);
  }
  max1 = array1[0];
  for(i=1; i<no; i++)
  {
    if(max1 < array1[i])
    {
      max1 = array1[i];
      count = i;
    }
  }

  for(j=0, i=0; i<no-1; i++,j++)
  {
    if(i < count)
    {       
      array2[i] = array1[j];
    }
    if(i >= count)
    {
    array2[i] = array1[j+1];
    }
  }

  for(i=0; i<no-1; i++)
  {
    printf("%d ",array2[i]);
  }
}


