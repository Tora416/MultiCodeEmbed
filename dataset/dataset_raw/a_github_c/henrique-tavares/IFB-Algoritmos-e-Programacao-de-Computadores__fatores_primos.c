#include <stdio.h>
#define true 1
#define false 0

int main(void)
{
    long int n;
    int vf = false, qtd = 0, primo = 2;

    do
    {
        printf("\nDigite um numero natural para calcular seus fatores primos: ");
        scanf("%li", &n);
        if (n < 0)
        {
            printf("ERRO! Favor digitar um numero natural\n");
        }
    } while (n < 0);

    if (n == 0)
    {
        printf("\nNao ha fatores primos de 0\n");
    }
    else if (n == 1)
    {
        printf("\n1 = 1\n");
    }
    else
    {
        printf("\n%.0li = ", n);
        while (n > 1)
        {
            while (vf = false)
            {
                for (int i = 2; i < primo; i++)
                {
                    if ((primo % i) == 0)
                    {
                        vf = true;
                    }
                }
                if (vf = false)
                {
                    primo++;
                }
            }
            while ((n % primo) == 0)
            {
                n = n / primo;
                qtd++;
            }
            if (qtd != 0)
            {
                printf("%i(%i) ", primo, qtd);
            }

            primo++;
            vf = false;
            qtd = 0;
        }
        printf("\n\n");
    }
}