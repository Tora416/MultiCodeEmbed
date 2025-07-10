#include <stdio.h>

int main()
{
    int qtd, n, qtd_total = 0;
    scanf ("%i", &qtd);

    for (int i=0; i<qtd; i++)
    {
        scanf ("%i", &n);

        while (n>=100)
        {
            n -= 100;
            qtd_total++;
        }
        
        if ((50<=n)&&(n<=99))
        {
            n -= 50;
            qtd_total++;
        } 

        if ((25<=n)&&(n<=49))
        {
            n -= 25;
            qtd_total++;
        }

        while ((10<=n)&&(n<=24))
        {
            n -= 10;
            qtd_total++;
        }

        if ((5<=n)&&(n<=9))
        {
            n -= 5;
            qtd_total++;
        }

        while ((2<=n)&&(n<=4))
        {
            n -= 2;
            qtd_total++;
        }

        if (n==1)
        {
            n--;
            qtd_total++;
        }
    
        printf ("%i notas\n", qtd_total);
        qtd_total = 0;

    }

    return 0;
}