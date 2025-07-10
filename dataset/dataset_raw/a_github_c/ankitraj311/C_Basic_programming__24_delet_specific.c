#include<stdio.h>
int main()
{
  int i=0,j=0,k=0,array1[100]={0},array2[100]={0},no=0,delete_no=0,delete_index=0,flag=0;
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
      flag = 1;
    }
  }

  if(flag == 1)
  {
    for(i=0; i<no-1; i++)
    {
      if( i < delete_index)
      {
        array2[i] = array1[i];
      }
      if( i >= delete_index)
      {
        array2[i] = array1[i+1];
      }
    }
    printf("\n");
    for(i=0; i<no; i++)
    {
    for(i=0; i<no-1; i++)
    {
      printf("%d ",array2[i]);
    }
  }
}
}
