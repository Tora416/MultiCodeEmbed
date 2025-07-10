

#include<stdio.h>
#include<string.h>
int main()
{
  int arr[100],no,j=0,temp=0,mid=0;
  printf("Enter length of array");
  scanf("%d",&no);




  for(int i = 0; i<no; i++)
  {
    scanf("%d",&arr[i]);
  }

  for(int i = 0; i<no; i++)
  {
    printf("%d ",arr[i]);
  }

  printf("\n");

  for(int i = 0; i<no; i++)
  {
    if(arr[i]<0)
    {
      if(i != j)
      {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
      j++;
    }
  }

  for(int i = 0; i<no; i++)
  {
    printf("%d ",arr[i]);
  }
}
