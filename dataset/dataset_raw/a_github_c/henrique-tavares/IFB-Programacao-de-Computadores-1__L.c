#include <stdio.h>

int main()
{
    int qtd, n, qtd_total, qtd100 = 0, qtd50 = 0, qtd25 = 0, qtd10 = 0, qtd5 = 0, qtd2 = 0, qtd1 = 0;
    scanf ("%i", &qtd);

    for (int i=0; i<qtd; i++)
    {
        scanf ("%i", &n);
        while (n>=100)
        {
            n -= 100;
            qtd100++;
        }
        
        if ((50<=n)&&(n<=99))
        {
            n -= 50;
            qtd50++;
        } 

        if ((25<=n)&&(n<=49))
        {
            n -= 25;
            qtd25++;
        }

        while ((10<=n)&&(n<=24))
        {
            n -= 10;
            qtd10++;
        }

        if ((5<=n)&&(n<=9))
        {
            n -= 5;
            qtd5++;
        }

        while ((2<=n)&&(n<=4))
        {
            n -= 2;
            qtd2++;
        }

        if (n==1)
        {
            n--;
            qtd1++;
        }
        
        qtd_total = qtd100+qtd50+qtd25+qtd10+qtd5+qtd2+qtd1;
        printf ("%i notas\n%i notas de 100\n%i notas de 50\n%i notas de 25\n%i notas de 10\n%i notas de 5\n%i notas de 2\n%i notas de 1\n", qtd_total, qtd100, qtd50, qtd25, qtd10, qtd5, qtd2, qtd1);
        qtd_total = 0;
        qtd100 = 0;
        qtd50 = 0;
        qtd25 = 0;
        qtd10 = 0;
        qtd5 = 0;
        qtd2 = 0;
        qtd1 = 0;
    }

    return 0;
}