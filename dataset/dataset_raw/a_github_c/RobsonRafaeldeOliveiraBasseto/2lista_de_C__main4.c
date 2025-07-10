#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned long int dec;
    unsigned long int c;
    unsigned long int d = 1;
    unsigned long int e = 0;
    unsigned long int f = 1;
    unsigned long int g;

    printf("Digite um numero decimal: ");
    scanf("%lu",&dec);


    while(dec != 0)
    {
        c = dec % 2;
        printf("Passo %3lu: %10lu/2, Resto = %3lu, Quociente = %8lu\n",d++,dec,c, dec / 2);

        dec /= 2;
        e += c * f;
        f *= 10;

    }
        printf("o numero em binario eh: %lu",e);
        printf("\n");


}
