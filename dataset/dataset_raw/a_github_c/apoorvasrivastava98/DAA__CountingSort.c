#include<stdio.h>
int count=0;
void counting_sort(int[],int,int);
void main()
{
    int n,k=0,A[30],i;
    printf("Enter the value of n \n");
    scanf("%d",&n);
    printf("Enter the values to be sorted\n");
    for (i=1;i<=n;i++)
    {
        scanf("%d",&A[i]);
        if (A[i]>k) 
        {
            k=A[i];
        }
    }
    counting_sort(A, k, n);
    printf("\nValue of count=%d",count);
}
void counting_sort(int A[], int k, int n)
{
    int i, j,B[30],C[100];
    count++;
    for (i=0;i<=k;i++)
    {
        C[i]=0;
        count++;
        }
        count++;
    for (j=1;j<=n;j++){
        C[A[j]]=C[A[j]]+1;
        count++;
        }
        count++;
    for (i=1;i<=k;i++){
        C[i]=C[i]+C[i-1];
        count++;
        }
        count++;
    for (j=n;j>=1;j--)
    {
        count++;
        B[C[A[j]]]=A[j];
        count++;
        C[A[j]]=C[A[j]]-1;
        count++;
    }
    printf("Array after sorting\n ");
    for (i=1;i<=n;i++)
        printf("%d ",B[i]);
}
