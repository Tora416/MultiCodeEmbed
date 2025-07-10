
#include<stdio.h>
#include<malloc.h>
void displayarr(int arr[],int len);
int removeDuplicates(int arr[],int n);
int main()
    {
    int *arr,i,n,sum=0;
    printf("Enter how many numbers you want to store into array");
    scanf("%d",&n);
    
    arr=(int *)malloc((n)*sizeof(int *));   
    
    printf("\nEnter %d elements",n);
    for(i=0;i<n;i++)
    scanf("%d",&arr[i]);
    
    n=removeDuplicates(arr,n);
    
    printf("\nAfter removing duplicates: ");
    displayarr(arr,n);
    return 0;
    }
int removeDuplicates(int arr[],int n)
    {
    int i,j=0,*temp,k;
    if(n==0||n==1)
        return n;
    
    temp=(int *)malloc((n)*sizeof(int *));
    
    for(i=0;i<n;i++)
        {
        for(j=i+1;j<n;)
            {
            if(arr[i]==arr[j])
                {
                for(k=j;k<n;k++)
                    arr[k]=arr[k+1];
                n--;
                }
            else
                j++;    
            }
        }
    return n;
    }
void displayarr(int arr[],int len)
    {
    int i;
    for(i=0;i<len;i++)
        printf("%d ",arr[i]);
    }
