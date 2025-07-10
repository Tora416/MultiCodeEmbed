

#include <stdio.h>
#include <stdlib.h>

void selection(int a[],int n)
{
    int p,j,min,temp;
    for(p=0;p<n-1;p++)
    {
        min=p;
        for(j=p+1;j<n;j++)
        {
            if(a[j]<a[min])
            {
                min=j;
            }
        }
        if(min!=p)
        {
            temp=a[p];
            a[p]=a[min];
            a[min]=temp;
        }
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
    printf("selection sort \n ");
    int a[5]={65,47,4,80,12};
    int n=5;
    printf("the elements in the array are :\n ");
    printarray(a,n);
    printf("\n after sorting elements in the array are :\n");
    selection(a,n);
    printarray(a,n);
    return EXIT_SUCCESS;
}
