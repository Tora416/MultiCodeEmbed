

#include <stdio.h>
#include <stdlib.h>
void linear(int a[],int n,int data)
{
    int i,result=0;
    for(i=0;i<n;i++)
    {
        if(a[i]==data)
        {
            result=1;
            break;
        }
    }
    if(result==0)
    {
        printf("the element is not found in the array \n");
    }
    else
    {
        printf("the element is  found in the array at index %d \n",i);
        printf("the element is  found in the array at position  %d \n",i+1);
    }
}
void printarray(int a[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d \t",a[i]);
}
int main(void) {
    printf("linear search \n");
    printf("searching for an  element in the array \n"); 
    printf("elements in the array are \n");
    int a[5]={15,24,36,14,22};
    int n=5;
    printarray(a,n);
    int data=36;
    printf("\n the searching element in the array is %d \n",data);
    linear(a,n,data);

    return EXIT_SUCCESS;
}
