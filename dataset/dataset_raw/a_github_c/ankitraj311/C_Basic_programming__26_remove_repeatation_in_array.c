#include<stdio.h>
int main()
{
  int i=0,j=0,k=0, no=0,insert_no=0,insert_index=0,flag=0,count = 0i, count2 = 0;
  printf("Enter Length of Array");
  scanf("%d",&no);
  int array1[no-1], array2[no-1];




  count = no;
  for(i=0; i<no; i++)
  {
    scanf("%d",&array1[i]);
  }
  for(i=0; i<no; i++)
  {
    printf("%d ",array1[i]);
  }
  
  for(i=0; i<no; i++)
  {
    for(j=i+1; j<no;)
    {
      if(array1[i] == array1[j])
      {
        for(k=j; k<count; k++)
    {
          array1[k] = array1[k+1];
    }
    no--;
      }
      else
      {
        j++;

      }
    }  
  }
  printf("Value of count is %d and count2 is %d",count,count2);
  printf("Array after Removal of Repetation\n");
  for(i=0; i<no; i++)
  {
    printf("%d ",array1[i]);
  }

}
