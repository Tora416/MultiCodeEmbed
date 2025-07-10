
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

int ispresent(int arr1[], int size_arr1, int arr2[], int index_val) 
{
  for(int i = 0; i<size_arr1; i++)
  {
    if(arr1[i] == arr2[index_val])
    {
      return 1;
    }
  }
  return 0;
}

int remove_repeat(int arr[], int size_arr) 
{
  for(int i = 0; i<size_arr; i++)
  {
    for(int j = i+1; j<size_arr;j++)
    { 
      if(arr[i] == arr[j])
      {
        for(int k = j; k<size_arr; k++)
    {
          arr[k] = arr[k+1];
    }
    size_arr--;
      }
    }
  }
  return size_arr;
}
void union_array(int arr1[], int arr2[], int size_arr1, int size_arr2)
{
  int total_size = size_arr1+size_arr2, arr3[total_size], index_val = 0, k = 0i, last_count = 0;

  for(int i = 0; i<size_arr1; i++)
  {
    arr3[k] = arr1[i];
    k++;
  }

  for(int i = 0; i<size_arr2; i++)
  {
    int val = ispresent(arr1,size_arr1,arr2,i); 
    if(val == 0)
    {
      arr3[k] = arr2[i];
      k++;
    }
  }

  printf("Array after Union :-");
  array_print(arr3,k);
}

int main()
{
  int arr1[] = {1,2,3,5,6,6,7,8,9,7,8,9,10}, arr2[] = {100,2,3,60,1,2,3,4,4,6,4,9,80,7,2,30,1} ,no,j=0,temp=0,mid=0,n=0;
  int size_arr1 = sizeof(arr1)/sizeof(int), size_arr2 = sizeof(arr2)/sizeof(int);
  array_print(arr1,size_arr1); 
  array_print(arr2,size_arr2); 
  size_arr1 = remove_repeat(arr1,size_arr1); 
  size_arr2 = remove_repeat(arr2,size_arr2); 
  array_print(arr1,size_arr1); 
  array_print(arr2,size_arr2); 
  union_array(arr1,arr2,size_arr1,size_arr2);
}
