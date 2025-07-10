

#include <stdio.h>
#include <stdlib.h>
void merge(int a[],int lb,int mid,int ub)
{
    int i,j,k,b[10];
    i=lb;
    j=mid+1;
    k=lb;
    while(i<=mid && j<=ub)
    {
        if(a[i]<a[j])
        {
            b[k]=a[i];
            i++;
            k++;
        }
        else
        {
            b[k]=a[j];
            j++;
            k++;
        }
    }
    if(i>mid)
    {
        while(j<=ub)
        {
            b[k]=a[j];
            j++;
            k++;
        }
    }
    else
    {
        while(i<=mid)
        {
            b[k]=a[i];
            i++;
            k++;
        }
    }
    for(k=lb;k<=ub;k++)
    {
        a[k]=b[k];
    }
}
void mergesort(int a[],int l,int r)
{
    int mid;
    if(l<r)
    {
        mid=(l+r)/2;
        mergesort(a,l,mid);
        mergesort(a,mid+1,r);
        merge(a,l,mid,r);
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
    printf("merge sort \n");
    int a[10]={45,78,96,12,63,80,69,71,85,11};
    int n=10;
    printf("the elements in the array are :\n ");
    printarray(a,n);
    printf("\n after sorting elements in the array are :\n");
    mergesort(a,0,n-1);
    printarray(a,n);
    return EXIT_SUCCESS;
}
