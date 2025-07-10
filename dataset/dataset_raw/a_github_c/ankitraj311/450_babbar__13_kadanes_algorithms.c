
#include<stdio.h>







void array_print(int arr[], int no)  
{
  for(int i = 0; i<no; i++)
  {
    printf("%d ",arr[i]);
  }
  printf("\n");
}


int cyclic_rotate(int arr1[], int size_arr1)
{
  int meh = 0, msf = 0; 
  for(int i = 0; i<size_arr1;i++)
  {
    meh = meh + arr1[i]; 

    if(msf<meh) 
    {
      msf = meh;
    }
    if(meh<0) 
    { 
      meh = 0;
    }
  }
  return meh;  
}


int main()
{
  int arr1[] = {-2,-3,4,-1,-2,1,5,-3}, no,j=0;
  int size_arr1 = sizeof(arr1)/sizeof(int);
  array_print(arr1,size_arr1);
  int sum = cyclic_rotate(arr1,size_arr1);
  printf("Sum is %d",sum);
}
