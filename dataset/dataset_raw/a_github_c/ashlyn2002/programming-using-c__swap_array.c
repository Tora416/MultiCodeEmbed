

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("swapping the elements in the array to another array \n"); 
    int n=5,i;
    printf("elements in the array  1 are \n");
    int a[5]={15,24,36,14,22};
    for(i=0;i<n;i++)
        printf("%d \t",a[i]);
    printf("\n");
    int temp[5];
    for(i=0;i<n;i++)
    {
        temp[i]=a[i];
    }
    printf("\n elements in the array  2 are \n");
    int b[5]={20,16,95,38,45};
    for(i=0;i<n;i++)
        printf("%d \t",b[i]);
    printf("\n after swapping the array \n");
    printf("\n elements in the array  1 are \n");
    for(i=0;i<n;i++)
    {
        a[i]=b[i];
        printf("%d \t",a[i]);
    }
    printf("\n elements in the array  2 are \n");
    for(i=0;i<n;i++)
    {
        b[i]=temp[i];
        printf("%d \t",b[i]);
    }
    return EXIT_SUCCESS;
}
