

#include <stdio.h>
#include <stdlib.h>
void insertion(int a[],int n)
{
    int i,j,temp;
    for(i=1;i<n;i++)
    {
        temp=a[i];
        j=i-1;
        while(j>=0 && a[j]>temp)
        {
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=temp;
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
    printf("insertion sort \n ");
    int a[5]={90,64,11,24,5};
    int n=5;
    printf("the elements in the array are :\n ");
    printarray(a,n);
    printf("\n after sorting elements in the array are :\n");
    insertion(a,n);
    printarray(a,n);
    return EXIT_SUCCESS;
}
