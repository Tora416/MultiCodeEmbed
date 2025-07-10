

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("insertion \n"); 
    printf("insert an element in the array \n");
    int a[100]={0};
    int n=10;
    int i;
    printf("the elements in the array are : \n");
    for(i=0;i<n;i++)
    {
        a[i]=i+4;
        printf("%d\t",a[i]);
    }
    int b=25,pos=3;
    printf("\n the element is going to insert is : %d \n",b);
    printf(" the element is going to insert at position is : %d \n",pos);
    n++;
    for(i=n-1;i>=pos;i--)
    {
        a[i]=a[i-1];
    }
    a[pos-1]=b;
    printf("\n after the insertion the elements in the array are \n");
    for(i=0;i<n;i++)
    {
        printf("%d\t",a[i]);
    }
    return EXIT_SUCCESS;
}
