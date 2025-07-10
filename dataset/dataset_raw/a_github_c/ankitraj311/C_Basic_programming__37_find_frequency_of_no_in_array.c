#include<stdio.h>
#include<stdlib.h>
int main()
{
  int i,j,k,no=0,max=0;
  printf("Enter Length of array\n");
  scanf("%d",&no);



  int *a = (int*)(malloc(no * sizeof(int)));
  printf("Enter Array numbers\n");
  for(i=0; i<no; i++)
  {
   scanf("%d",&a[i]);
  }
  for(i=0; i<no; i++)
  {
    printf("%d ",a[i]);
  }
  max = a[0];
  for(i=0; i<no; i++)
  {
    if(max < a[i])
    { 
      max = a[i];
    }
  }
  printf("Value of Max is %d",max);
  max+=1;
  int b[max];
  a = (int*)(realloc(a,max * sizeof(int)));
  for(i=0; i<max; i++)
  {
    b[i] = 0;
    if(i>=no)
    {
      a[i] = 0;
    }
  }

  
  for(i=0; i<=max; i++)
  {
    if(a[i] != 0)
    {
      b[a[i]] = b[a[i]] + 1;
    }
  }
  printf("Numbers Repeated odd numbers of Times\n");
  for(i=0; i<max; i++)
  {
    if(b[i] != 0)
    {
      printf("%d is repeated %d times\n",i,b[i]);
    }
  }
}
