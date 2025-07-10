#include<stdio.h>
#include<string.h>
void array_print(int arr[], int no)
{
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



int sort(int arr[], int size)
{
  int low,mid,high;
  low = mid = 0;
  high = (size-1);
  while(mid<=high)
  {
    switch (arr[mid]) 
    { 
      case 0: 
          swap(&arr[low++], &arr[mid++]); 
          break; 
      case 1: 
          mid++; 
          break; 
      case 2: 
          swap(&arr[mid], &arr[high--]); 
          break;
    }
  }
}




   
int main()
{
  int arr[] = {0,1,1,0,1,2,1,2,0,0,0,1};
  int no = 12;
  printf("Array is :- ");
  array_print(arr,no);
  sort(arr,no);
  printf("\n");
  array_print(arr,no);
}
