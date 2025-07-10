
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





void cyclic_rotate(int arr1[], int size_arr1)
{
  int last_element,i=0;
  last_element = arr1[size_arr1-1];
  for(i = size_arr1-1; i > 0; i--)
    arr1[i] = arr1[i-1];
  arr1[0] = last_element;
}

int main()
{
  int arr1[] = {1,2,3,4, 5,}, no,j=0;
  int size_arr1 = sizeof(arr1)/sizeof(int);
  array_print(arr1,size_arr1); 
  cyclic_rotate(arr1,size_arr1);
  array_print(arr1,size_arr1); 
}
