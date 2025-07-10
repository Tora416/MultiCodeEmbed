#include<stdio.h>
int main()
{
  int i,j,k,array1[100],array2[100],no=0,delete_no=0,delete_index=0;
  printf("Enter Length of Array");
  scanf("%d",&no);





  for(i=0; i<no; i++)
  {
    scanf("%d",&array1[i]);
  }

  for(i=0; i<no; i++)
  {
    printf("%d ",array1[i]);
  }

  printf("Enter number to delete it from Array\n");
  scanf("%d",&delete_no);

  for(i=0; i<no; i++)
  {
    if(array1[i] == delete_no)
    {
      printf("Number is %d Index is %d",array1[i],i);
      delete_index = i;
    }
  }

  printf("\n");

  for(j=0; j<no-1; j++)
  {
    if(j < delete_index)
    {
      array2[j] = array1[j];
    }
    if(j >= delete_index)
    {
      array2[j] = array1[j+1];
    }
  }
  printf("\n");
  for(i=0; i<no-1; i++)
  {
    printf("%d ",array2[i]);
  }
}
