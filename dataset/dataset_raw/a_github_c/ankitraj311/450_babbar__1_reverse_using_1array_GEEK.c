#include<stdio.h>
#include<string.h>









void array_print(int arr[], int no)
{
  for(int i = 0; i<no; i++)
  {
    printf("%d ",arr[i]);
  }
}

void reverse_array(int arr[], int START, int END)
{
  int temp = 0;
  while(START<END)
  {
    temp = arr[END];
    arr[END] = arr[START];
    arr[START] = temp;
    START++;
    END--;
  }
}
int main()
{
  int arr[100],no,j=0,temp=0,mid=0,n=0;
  printf("Enter length of array");
  scanf("%d",&no);




  for(int i = 0; i<no; i++)
  {
    scanf("%d",&arr[i]);
  }
  array_print(arr,no);
  reverse_array(arr,0,no-1);
  printf("\n");
  array_print(arr,no);
}
