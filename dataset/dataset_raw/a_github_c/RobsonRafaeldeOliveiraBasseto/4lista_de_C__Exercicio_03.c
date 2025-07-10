
#include <stdio.h>
#include <stdlib.h>

int main()
{
    float a[10],b[10];
    int i;

    for(i=0; i<10; i++)
    {
        printf(" digite o %d valor: ",i);
        scanf("%f",&a[i]);
    }
    for(i=0; i<10; i++)
        b[i] = a[i] * a[i];
    printf("\n\nConjunto 1: \n");

    for(i=0; i<10; i++)
    printf("\n%2.f ",a[i]);
    printf("\n\nConjunto 2: \n");

    for(i=0; i<10; i++)

        printf(" \n%2.f ",b[i]);




return 0;
}
