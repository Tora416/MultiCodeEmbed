#include<stdio.h>
int main()
{
  int i=0,j=0,k=0,len_array1=0,len_array2=0,temp=0;
  printf("Enter Length of array1 and array2");
  scanf("%d%d",&len_array1,&len_array2);
  int array1[len_array1],array2[len_array2],array3[len_array1+len_array2];



  printf("Enter Element of Array1\n");
  for(i=0; i<len_array1; i++)
  {
    scanf("%d",&array1[i]);
  }
  printf("Enter Element of Array2\n");
  for(i=0; i<len_array2; i++)
  {
    scanf("%d",&array2[i]);
  }

  for(i=0;i<len_array1;i++)
  {
    array3[j] = array1[i];
    j++;
  }
  for(i=0;i<len_array2;i++)
  {
    array3[j] = array2[i];
    j++;
  }

  for(i=0;i<len_array1+len_array2;i++)
  {
    printf("%d ",array3[i]);
  }
  printf("After Sorting\n");
  
  for(i=0;i<len_array1+len_array2;i++)
  {
    for(j=i+1;j<len_array1+len_array2;j++)
    {
      if(array3[i] > array3[j])
      {
        temp = array3[i];
    array3[i] = array3[j];
    array3[j] = temp;
      }
    }  
  }

  for(i=0;i<len_array1+len_array2;i++)
  {
    printf("%d ",array3[i]);
  }
}
