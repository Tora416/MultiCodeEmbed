

#include <stdio.h>
#include <stdlib.h>
void printarray(int a[],int n)
{
    for(n=0;n<5;n++)
        printf("%d \t",a[n]);
}
int main(void) {
    printf("printing the array in the descending odder \n "); 
    printf("elements in the array are \n");
    int a[5]={15,24,36,14,22};
    int n=5,temp;
    printarray(a,n);
    printf("\n array in the descending odder is \n ");
    int i,j;
    for(i=0;i<5;i++)
    {
        for(j=i+1;j<5;j++)
        {
            if(a[j]>a[i])
            {
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
    printarray(a,n);
    return EXIT_SUCCESS;
}
