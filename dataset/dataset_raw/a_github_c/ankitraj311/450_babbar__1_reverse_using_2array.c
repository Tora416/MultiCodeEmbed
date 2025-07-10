#include<stdio.h>
#include<string.h>
int main()
{
  int arr[100],arr1[100],no,j=0;
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
  for(int i = no-1; i>=0; i--)
  {
    arr1[j] = arr[i];
    j++;
  }

  for(int i = 0; i<no; i++)
  {
    printf("%d ",arr1[i]);
  }
}
