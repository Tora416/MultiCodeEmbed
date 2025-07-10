#include <stdio.h>
     int count =0;
       int partition(int [50],int,int); 
       void quick_sort(int[50],int,int);
     void main()
      {
       void getdata(int[50],int);
       void putdata(int[50],int);
       int i,a[50],n;
       printf("Enter the value of n \n");
       scanf("%d",&n);
       getdata(a,n);
       printf("Before sorting \n");
       putdata(a,n);
       quick_sort(a,0,n-1);
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
        
    int partition(int a[50],int p,int r)
   {
    int x,i,j,temp;
    x=a[r];
    i=p-1;
    count++;
    for(j=p;j<=r-1;j++)
    {
        count++;
        if(a[j]<=x)
        {
        count++;
            i=i+1;
        count++;
            temp=a[j];
        count++;
            a[j]=a[i];
        count++;
            a[i]=temp;
        count++;
        }
        count++;
    }
    count++;
    temp =a[r];
    count++;
    a[r]=a[i+1];                       
    count++;
    a[i+1]=temp;
    count++;
    return i+1;
    }

void quick_sort(int a[50],int p,int r)
{   
    int q;
    count++;
    if(p<r)
    {
        count++;
        q=partition(a,p,r);
        count++;
        quick_sort(a,p,q-1);
        count++;
        quick_sort(a,q+1,r);
        count++;
    }
}
