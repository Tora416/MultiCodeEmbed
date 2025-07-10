#include<stdio.h>
#include<string.h>
void array_print(int arr[], int no)
{
  for(int i = 0; i<no; i++)
  {
    printf("%d ",arr[i]);
  }
}



int kmin(int arr[], int size, int k)
{
  int  temp = 0, count = 0, index = 0;

  while(count <= k)
  { 
    int min = arr[count], index = count;
    for(int i = count; i < size; i++)
    {
      if(min > arr[i])
      {
        min = arr[i];
    index = i;
      }
    }
    if(count != index)
    {
      temp = arr[index];
     
      arr[index] = arr[count];
      
      arr[count] = temp;
      
    }
    count++;
    
  }
  return (count-1);
}
int main()
{
  int arr[100] = {1000, 11, 445, 1, 330, 3000};
  int no = 6,k=0,rindex=0;
  printf("Array is :- ");
  array_print(arr,no);
  printf("Enter value of kth");
  scanf("%d",&k);
  rindex = kmin(arr,(no-1),(k-1));
  printf("rindex is %d\n",rindex);
  printf("kth Min value is %d",arr[rindex]);
}
