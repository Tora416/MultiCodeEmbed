#include<stdio.h>
#include<string.h>









void array_print(int arr[], int no)
{
  for(int i = 0; i<no; i++)
  {
    printf("%d ",arr[i]);
  }
  printf("\n");
}

void union_array(int arr1[], int arr2[])
{
  int size_arr1 = (sizeof(arr1)/sizeof(int)), size_arr2 = (sizeof(arr2)/sizeof(int));
  int arr3[size_arr1+size_arr2], j = 0;
  for(int i = 0; i<size_arr1; i++)
  {
    arr3[j] = arr1[i];
    j++;
  }
  for(int i = 0; i<size_arr2; i++)
  {
    arr3[j] = arr1[i];
    j++;
  }
  array_print(arr3,size_arr1+size_arr2);
}

int main()
{
  int arr1[] = {1,2,3,5,6,7,8,9,10}, arr2[] = {10,2,3,6,4,9,8,7,2,3,1} ,no,j=0,temp=0,mid=0,n=0;
  array_print(arr1,sizeof(arr1)/sizeof(int));
  array_print(arr2,sizeof(arr2)/sizeof(int));
  union_array(arr1,arr2);
}
