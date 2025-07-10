#include <stdio.h>
int count=0;
void selectionsort(int[],int);
void main()
{
     void getdata(int[50],int);  
     void putdata(int[50],int);  
     int i,a[50],n;  
     printf("Enter the value of n\n");    
     scanf("%d",&n);  
     getdata(a,n);    
     printf("Before sorting \n");    
     putdata(a,n);
     selectionsort(a,n);     
     printf("After sorting \n");    
     putdata(a,n);     
     printf("value of count=%d \n",count);
}
    void getdata(int x[50],int n)

       {
        int k;
        printf("enter the value  for sorting\n");
        for(k=0;k<n;k++)
        {
         scanf("%d",&x[k]);
        } }
     void putdata(int x[50], int n)

         {
          int k;
          for(k=0;k<n;k++)
         {
          printf("%d\t",x[k]);
           }
          printf("\n");
          }
void selectionsort(int numbers[],int array_size)
{
    int i,j,T,min;
    count++;
    for(i=0;i<array_size;i++)
    {
        count++;
        min=i;
        count++;
        for(j=i+1;j<array_size;j++)
        {
            count++;
            if(numbers[j]<numbers[min])
            {
                count++;
                min=j;
                count++;
            }
        }
        count++;
        if(i!=min)
        {
        count++;
        T=numbers[min];
        count++;
        numbers[min]=numbers[i];
        count++;
        numbers[i]=T;
        count++;
        }
    }
}
