#include<stdio.h>
int count = 0;
void main()
{
  void getdata(int[50],int);
  void putdata(int[50],int);
  void bubble_sort(int a[50],int);
    int a[50],n;
    printf("Enter the value of n\n");
    scanf("%d",&n);
    getdata(a,n);
    printf("Before sorting \n");
    putdata(a,n);
    bubble_sort( a,n);
    printf("After sorting \n");
    putdata(a,n);
    printf("Value of count=%d \n",count);
}
    void getdata(int x[50],int n)
      {
        int k;
        printf("enter the value for sorting\n");
        for(k=0;k<n;k++)
        {
         scanf("%d",&x[k]);
        } 
       }
    void putdata(int x[50], int n)
       {
          int k;
          for(k=0;k<n;k++)
         {
          printf("%d\t",x[k]);
         }
          printf("\n");
       }
    void bubble_sort(int a[50],int n)
    {
       int i,j,temp;
       count++;
       for(i=1;i<n;i++)
       {
           count++;
           count++;
           for(j=0;j<n-i;j++)
           {
               count++;
               count++;
               if(a[j]>a[j+1])
               {
                   count++;
                   temp=a[j];
                   count++;
                   a[j]=a[j+1];
                   count++;
                   a[j+1]=temp;
                   count++;
               }
           }
       }
    }
