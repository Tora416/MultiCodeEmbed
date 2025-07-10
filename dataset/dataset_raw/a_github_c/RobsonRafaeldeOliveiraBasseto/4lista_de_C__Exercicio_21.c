
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[10];
    int b[10];
    int c[10];

    int i;
                printf("--------------------------------------\n");
                printf("digite um numero para o primeiro vetor\n");
                printf("--------------------------------------\n\n");

    for(i=0;i<10;i++) 
    {
        printf("digite um numero: ");
        scanf("%d",&a[i]);
    }

                printf("--------------------------------------\n");
                printf("digite um numero para o segundo vetor\n");
                printf("--------------------------------------\n\n");

    for(i=0;i<10;i++) 
    {
        printf("digite um numero: ");
        scanf("%d",&b[i]);
    }

                printf("\n------------------------------------------\n");
    for(i=0;i<10;i++) 
    {
        c[i] = a[i] - b[i];
        printf("[%d] - [%d] = [%d]\n",a[i],b[i],c[i]);
    }
                printf("\n------------------------------------------\n");






}
