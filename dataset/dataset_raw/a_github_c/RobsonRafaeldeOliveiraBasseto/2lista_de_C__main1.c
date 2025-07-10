#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    int b;
    float c;
    int d =0;
    int e = 0;
    int f = 0;
    int g = 0;

    printf("Digite o tamanho da sequencia: ");
    scanf("%d",&a);

    for(b = 0; b < a; b++)
    {
        printf("Digite os numeros: ");
        scanf("%f",&c);

        if(c >= 0 && c <= 25)
        {
            d++;
        }else if(c >= 26 && c <= 50)
        {
            e++;
        }else if(c >= 51 && c <= 75)
        {
            f++;
        }else if(c >= 76 && c <= 100)
        {
            g++;
        }

    }
        printf("[0...25]: %d\n",d);
        printf("[26...50]: %d\n",e);
        printf("[51...75]: %d\n",f);
        printf("[76...100]: %d\n",g);




}
