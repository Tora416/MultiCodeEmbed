#include<stdlib.h>
#include<stdio.h>
#define FOR(i,a,b) for(int i=a;i<b;i++)
int* takeInput(int n)
{
    int* arr=(int*)malloc(n*sizeof(int));
    int k;
    FOR(i,0,n)
    {
        scanf("%d",&k);
        arr[i]=k;
    }
    return arr;
}
void bubbleSort(int n,int* arr)
{
    FOR(i,0,n-1)
    {
        FOR(j,0,n-i-1)
        {
            if(arr[j]>arr[j+1])
            {
                arr[j]=arr[j]^arr[j+1];
                arr[j+1]=arr[j]^arr[j+1];
                arr[j]=arr[j]^arr[j+1];
            }
        }
    }
}
int main()
{
    int n;
    scanf("%d\n",&n);
    int* arr=takeInput(n);
    bubbleSort(n,arr);
    FOR(i,0,n)
    {
        printf("%d\t",arr[i]);
    }
    printf("\n");
    return 0;
}