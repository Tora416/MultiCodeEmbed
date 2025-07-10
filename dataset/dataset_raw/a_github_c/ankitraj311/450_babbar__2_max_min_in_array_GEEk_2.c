#include<stdio.h>
#include<string.h>
struct pair
{
  int min;
  int max;
};




struct pair max_min_array(int arr[], int low, int high)
{
  struct pair minmax,mml,mmr;
  int mid;

  if( low == high)
  {
    minmax.max = arr[low];
    minmax.min = arr[low];
    return minmax;
  }

  if(high == low+1)
  {
    if(arr[low]>arr[high])
    {
      minmax.max = arr[low];
      minmax.min = arr[high];
    }
    else
    {
      minmax.min = arr[low];
      minmax.max = arr[high];
    }
    return minmax;
  }

  mid = (low+high)/2;
  mml = max_min_array(arr, low, mid);
  mmr = max_min_array(arr, mid+1, high);
  
  if(mml.min < mmr.min)
    minmax.min = mml.min;
  else
    minmax.min = mmr.min;

  if(mml.max > mmr.max)
    minmax.max = mml.max;
  else
    minmax.max = mmr.max;
  return minmax;
}

int main()
{
  int arr[100] = {1000, 11, 445, 1, 330, 3000};
  int no = 6;
  struct pair minmax = max_min_array(arr,0,no-1);
  printf("Max value is %d \nMin value is %d",minmax.min,minmax.max);
}
