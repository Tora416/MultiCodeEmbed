#include<stdio.h>
int count = 0;
void main()
{
  void getdata(int[50],int);
  void putdata(int[50],int);
  int binary_search(int a[50],int,int);
    int a[50],n,item,loc;
    printf("Enter the value of n\n");
    scanf("%d",&n);
    getdata(a,n);
    printf("Enter the item to be searched\n");
    scanf("%d",&item);
    printf("The given array is \n");
    putdata(a,n);
    loc=binary_search( a,n,item);
    if(loc>=0)
{
printf("element found at %d\n",loc);
}
else
{
printf("Item not found\n");
}
   
    printf("Value of count=%d \n",count);
}
    void getdata(int x[50],int n)
      {
        int k;
        printf("enter the values in the array\n");
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
       int binary_search(int x[50],int n,int item)
       {
        int i,lb=0,ub=n-1,mid;
        count++;
        while(lb<=ub)
        {
         count++;
         mid=(lb+ub)/2;
         count++;
         if(x[mid]==item)
            {
            count++;
            return mid;
            count++;
            }
            
         else if(item>x[mid])
            {
            count++;
            lb=mid+1;
            count++;
            }
            
         else
            {
            count++;
            ub=mid-1;
            count++;
            }
        }
        count++;
        return -1;
        count++;
       }

