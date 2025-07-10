

#include <stdio.h>
#include <stdlib.h>
void elemswap(int *x,int *y)
{
    int temp;
    temp=*x;
    *x=*y;
    *y=temp;
}
int sort(int a[],int l,int r)
{
    int key,start,end;
    key=a[l];
    start=l;
    end=r;
    if(start<end)
    {
        if(a[start]<=key)
        {
            start++;
        }
        if(a[end]>key)
        {
            end--;
        }
        if(start<end)
        {
            elemswap(&a[start],&a[end]);
        }
    }
    elemswap(&a[end],&a[l]);
    return end;
}
void quicksort(int a[],int l,int r)
{
    int loc;
    if(l<r)
    {
        loc=sort(a,l,r);
        quicksort(a,l,loc);
        quicksort(a,loc+1,r);
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
    printf("quick sort \n");
    int a[]={70,89,2,14,56,33,90};
    int n=sizeof(a)/sizeof(a[0]);
    printf("the elements in the array are :\n ");
    printarray(a,n);
    printf("\n after sorting elements in the array are :\n");
    quicksort(a,0,n-1);
    printarray(a,n);
    return EXIT_SUCCESS;
}
