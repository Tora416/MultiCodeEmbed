#include <stdio.h>
int count=0;
void max_heapify(int[100],int,int);
void build_max_heap(int[100],int);
void heapsort(int[100],int);
    void main()
    {
        void getdata(int[100],int);  
        void putdata(int[100],int);  
        int a[100],n;  
        printf("Enter the value of n\n");    
        scanf("%d",&n);  
        getdata(a,n);    
        printf("Before sorting \n");    
        putdata(a,n);
        heapsort(a,n);
        printf("After sorting \n");    
        putdata(a,n);     
        printf("value of count=%d \n",count);
    }
    void getdata(int x[100],int n)
    {
        int k;
        printf("enter the value  for sorting\n");
        for(k=0;k<n;k++)
        {
         scanf("%d",&x[k]);
        } 
    }
    void putdata(int x[100], int n)
    {
          int k;
          for(k=0;k<n;k++)
         {
          printf("%d\t",x[k]);
         }
          printf("\n");
    }
    void max_heapify(int a[100],int n,int i)
    {
        int temp;
        int largest=i;
        int left=2*i+1;
        int right=2*i+2;
        count++;
        if(left<n && a[left]>a[largest])
        {
            count++;
            largest=left;
            count++;
        }
        count++;
        if(right<n && a[right]>a[largest])
        {
            count++;
            largest=right;
            count++;
        }
        count++;
        if(largest!=i)
        {
            count++;
            temp=a[i];
            count++;
            a[i]=a[largest];
            count++;
            a[largest]=temp;
            count++;
            max_heapify(a,n,largest);
            count++;
        }
    }
    void build_max_heap(int a[100],int n)
    {
        int i;
        count++;
        for(i=(n/2)-1;i>=0;i--)
        {
            count++;
            max_heapify(a,n,i);
            count++;
        }
    }
    void heapsort(int a[100],int n)
    {
        int temp,i;
        count++;
        build_max_heap(a,n);
        count++;
        for(i=n-1;i>0;i--)
        {
            count++;
            temp=a[0];
            count++;
            a[0]=a[i];
            count++;
            a[i]=temp;
            count++;
            max_heapify(a,i,0);
            count++;
        }
    }
