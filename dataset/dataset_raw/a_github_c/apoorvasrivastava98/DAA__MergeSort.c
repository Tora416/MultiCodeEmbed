#include <stdio.h>
     int count =0;
     void merge(int[50],int,int,int); 
     void merge_sort(int[50],int,int); 
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
       merge_sort(a,0,n-1);
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
     void merge(int a[], int p, int q, int r) 
        { 
         int i, j, k; 
         int n1 =q-p+1; 
         int n2 =r-q; 
         count++;
         int L[n1],R[n2]; 
         count++;
         for(i=0;i<n1;i++)
          {
              count++;
              count++;
           L[i]=a[p+i];
           count++;
          }
         for(j=0;j<n2;j++)
          {
              count++;
              count++;
           R[j]=a[q+1+j];
           count++;
          }
         i=0; 
         j=0; 
         k=p; 
         count++;
         while(i<n1 && j<n2) 
          {
              count++;
           if(L[i] <= R[j]) 
            {
                count++;
            a[k]=L[i]; 
            count++;
            i++; 
            count++;
            } 
           else 
            {
                count++;
            a[k]=R[j];
            count++;
            j++; 
            count++;
            } 
            count++;
           k++;
           
          } 
          
         while(i<n1) 
          {
              count++;
           a[k]=L[i];
           count++;
           i++;
           count++;
           k++; 
           count++;
          } 
          
         while(j<n2) 
          {
           count++;
           a[k]=R[j];
           count++;
           j++; 
           count++;
           k++; 
           count++;
          }
        } 
       void merge_sort(int a[50],int p,int r)
        {
         int q;
         count++;
     if(p<r)
       { 
             count++;
             q=(p+r)/2;
             count++;
             merge_sort(a,p,q);
             count++;
             merge_sort(a,q+1,r);
             count++;
             merge(a,p,q,r);
             count++;
            }
           }
