#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int bSearch(int arr[],int n,int val,int* p){
    static int c=0;
    static int l=0;
    if(n==0){
        printf("ERROR: Empty list\n");
        exit(1);
    }
    if(n<l){
        printf("ERROR:Not found\n");
        exit(1);
    }
    int m=(l+n)/2;
    if(arr[m]==val){
        *p=m;
        return c;
    }
    c++;
    if(arr[m]>val)
        return bSearch(arr, m-1, val, p);
    else
    {
        l=m+1;
        return bSearch(arr, n, val, p);
    }
}
int main()
{
    int arr[MAX], pos, n, val, passes;
    
    scanf("%d",&n);
    
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);
    
    scanf("%d",&val);
    passes = bSearch(arr, n, val, &pos);
    printf("%d found at index: %d. Number of passes: %d", val, pos, passes);
    return 0;
}