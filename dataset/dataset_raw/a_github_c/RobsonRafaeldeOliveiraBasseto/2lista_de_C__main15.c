#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    int b;
    int c;
    int d = 0;
    int cont = 0;

    printf("digite o tamanho da sequencia: ");
    scanf("%d",&a);


    for(b = 0;b < a; b++)
    {
        printf("digite um numero: ");
        scanf("%d",&c);

        if(c < d)
        {
            cont++;

            d = 0 + c;

        }

    }

        if(cont <= 0)
        {
            printf("esta ordenado.");

        }else
        {
            printf("nao esta ordenada.");
        }

}
