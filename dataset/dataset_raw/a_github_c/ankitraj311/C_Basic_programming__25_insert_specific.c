#include<stdio.h>
int main()
{
  int i=0,j=0,k=0,array1[100]={0},array2[100] = {0}, no=0,insert_no=0,insert_index=0,flag=0;
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

  printf("Enter number to insert and position it from Array\n");
  scanf("%d%d",&insert_no,&insert_index);
  insert_index = insert_index - 1;
  
  for(i=0; i<no+1; i++)
  {
    if( i < insert_index)
    {
      array2[i] = array1[i];
    }
    if( i == insert_index)
    {
      array2[i] = insert_no;
    }
    if( i > insert_index)
    {
      array2[i] = array1[i-1];
    }
  }

  printf("\n");

  for(i=0; i<no+1; i++)
  {
    printf("%d ",array2[i]);
  }

}
