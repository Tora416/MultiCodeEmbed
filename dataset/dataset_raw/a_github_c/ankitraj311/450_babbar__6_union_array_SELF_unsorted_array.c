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

void union_array(int arr1[], int arr2[], int size_arr1, int size_arr2)
{
  int total_size = size_arr1+size_arr2;
  int arr3[total_size], j = 0;
  for(int i = 0; i<size_arr1; i++)
  {
    arr3[j] = arr1[i];
    j++;
  }
  for(int i = 0; i<size_arr2; i++)
  {
    arr3[j] = arr2[i];
    j++;
  }
  printf("Array befor Union :-");
  array_print(arr3,total_size);
  for(int i = 0; i<total_size; i++)
  {
    for(int j = i+1; j<total_size;)
    {
      if(arr3[i] == arr3[j])
      {
        for(int k = j; k<total_size; k++)
    {
          arr3[k] = arr3[k+1];
    }
    total_size--;
      }
      else
      {
        j++;
      }
    }
  }
  printf("Array after Union :-");
  array_print(arr3,total_size);
}

int main()
{
  int arr1[] = {1,2,3,5,6,7,8,9,10}, arr2[] = {10,2,3,6,4,9,8,7,2,3,1} ,no,j=0,temp=0,mid=0,n=0;
  int size_arr1 = sizeof(arr1)/sizeof(int), size_arr2 = sizeof(arr2)/sizeof(int);
  array_print(arr1,size_arr1);
  array_print(arr2,size_arr2);
  union_array(arr1,arr2,size_arr1,size_arr2);
}
