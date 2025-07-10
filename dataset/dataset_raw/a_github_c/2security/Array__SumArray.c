
#include<stdio.h>
#include<malloc.h>
void displayarr(int arr[],int len);
int main()
    {
    int *arr,i,n,sum=0;
    printf("Enter how many numbers you want to store into array");
    scanf("%d",&n);
    
    arr=(int *)malloc((n)*sizeof(int *));   
    
    printf("Enter %d elements",n);
    for(i=0;i<n;i++)
    scanf("%d",&arr[i]);
    
    for(i=0;i<n;i++)
        sum=sum+arr[i];
        
    printf("Sum of the array=%d",sum);
    return 0;
    }

void displayarr(int arr[],int len)
    {
    int i;
    printf("After delete operation the array is:\n");
    for(i=0;i<len;i++)
        printf("%d ",arr[i]);

    }
