#include<stdio.h>
#include<stdlib.h>
#define MAX 100
void RestoreHeapUp(int HEAP[],int index)
{
    int val=HEAP[index];
    while(index>1 && (HEAP[index/2]<val))
    {
        HEAP[index]=HEAP[index/2];
        index=index/2;
    }
    HEAP[index]=val;
}
void RestoreHeapDown(int HEAP[],int index,int n)
{
    int val=HEAP[index];
    int j=index*2;
    while(j<=n)
    {
        if(j<n && HEAP[j]<HEAP[j+1])
        j++;
        if(HEAP[j]<HEAP[j/2])
        break;
        else
        {
            HEAP[j/2]=HEAP[j];
            j=j*2;
        }
        HEAP[j/2]=val;
    }
}
void main()
{
    int HEAP[MAX],i,j,n,temp;
    printf("\nEnter the value of n:");
    scanf("%d",&n);
    printf("\nEnter the values:");
    for(i=1;i<=n;i++)
    {
        scanf("%d",&HEAP[i]);
        RestoreHeapUp(HEAP,i);
    }
    j=n;
    for(i=1;i<=j;i++)
    {
        temp=HEAP[1];
        HEAP[1]=HEAP[n];
        HEAP[n]=temp;
        n=n-1;
        RestoreHeapDown(HEAP,1,n);
    }
    n=j;
    printf("\nThe sorted array:\n");
    for(i=1;i<=n;i++)
    {
        printf("\t%d",HEAP[i]);
    }
}
