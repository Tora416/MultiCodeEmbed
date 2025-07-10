

#include <stdio.h>
void elemsw(int *x,int *y)
{
    int temp;
    temp=*x;
    *x=*y;
    *y=temp;
}
void sort(int a[],int n,int i)
{
    int large,l,r;
    large=i;
    l=2*i+1;
    r=2*i+2;
    while(l<n && a[l]>a[large])
    {
        large=l;
    }
    while(r<n && a[r]>a[large])
    {
        large=r;
    }
    if(large!=i)
    {
        elemsw(&a[large],&a[i]);
        sort(a,n,large);
    }
}
void heapsort(int a[],int n)
{
    int i;
    for(i=(n/2)-1;i>=0;i--)
    {
        sort(a,n,i);
    }
    for(i=n-1;i>=0;i--)
    {
        elemsw(&a[0],&a[i]);
        sort(a,i,0);
    }
}
void printarray(int a[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d\t",a[i]);
}
int main(void) {
    printf("sorting the elements in the array \n"); 
    printf("heap sort \n");
    int a[]={15,12,9,54,60,45};
    int n=sizeof(a)/sizeof(a[0]);
    printf("the elements in the array are :\n ");
    printarray(a,n);
    printf("\n after sorting elements in the array are :\n");
    heapsort(a,n);
    printarray(a,n);
}
