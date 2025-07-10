#include<stdio.h>
#include<string.h>
struct pair
{
  int min;
  int max;
};




struct pair max_min_array(int arr[], int no)
{
  struct pair minmax;
  if( no == 1)
  {
    minmax.max = arr[0];
    minmax.min = arr[0];
    return minmax;
  }
  if(arr[0] > arr[1])
  {
    minmax.max = arr[0];
    minmax.min = arr[1];
  }
  else
  {
    minmax.max = arr[1];
    minmax.min = arr[0];
  }
  
  for(int i = 0; i<no; i++)
  {
    if(arr[i] < minmax.min)
      minmax.min = arr[i];
    else if(arr[i] > minmax.max)
      minmax.max = arr[i];
  }
  return minmax;
}

int main()
{
  int arr[100] = {1000, 11, 445, 1, 330, 3000};
  int no = 6;
  struct pair minmax = max_min_array(arr,no);
  printf("Max value is %d \nMin value is %d",minmax.min,minmax.max);
}
