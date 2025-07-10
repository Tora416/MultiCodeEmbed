#include<stdio.h>
#include<string.h>
void array_print(int arr[], int no)
{
  for(int i = 0; i<no; i++)
  {
    printf("%d ",arr[i]);
  }
}



void max_min_array(int arr[], int max, int min, int no)
{
  for(int i = 0; i<no; i++)
  {
    if(min>arr[i])
    {
      min = arr[i];
    }
    else
    {
      max = arr[i];
    }
  }
  printf("Max is %d Min is %d",max,min);
}

int main()
{
  int arr[100],no,j=0,temp=0,mid=0,max = 0, min = 0;
  printf("Enter length of array");
  scanf("%d",&no);
  for(int i = 0; i<no; i++)
  {
    scanf("%d",&arr[i]);
  }
  printf("Array is :- ");
  array_print(arr,no);
  min = arr[0];
  max = arr[0];
  max_min_array(arr,max,min,no);  
}
