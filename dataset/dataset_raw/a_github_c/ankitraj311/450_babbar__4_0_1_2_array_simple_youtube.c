#include<stdio.h>
#include<string.h>









void array_print(int arr[], int no)
{
  printf("Array is :- ");
  for(int i = 0; i<no; i++)
  {
    printf("%d ",arr[i]);
  }
}

int swap(int* a, int* b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void sort012(int arr[], int size)
{
  int low,mid,high;
  low = mid = 0;
  high = (size-1);
  while(mid<=high)
  {
    if(arr[mid]==0)
    {
      swap(&arr[low], &arr[mid]);
      low++;
      mid++;
      continue;
    }
    if(arr[mid]==1)
    {
      mid++;
      continue;
    }
    if(arr[mid]==2)
    {
      swap(&arr[mid], &arr[high]);
      high--;
      continue;
    }
  }
}

int main()
{
  int arr[] = {0,1,1,0,0,2,1,2,0,0,0,1};
  int no = 12;
  array_print(arr,no);
  sort012(arr,no);
  printf("\n");
  array_print(arr,no);
}
