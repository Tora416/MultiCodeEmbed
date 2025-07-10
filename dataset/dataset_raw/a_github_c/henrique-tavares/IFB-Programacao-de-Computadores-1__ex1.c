#include <stdio.h>
#define true 1
#define false 0

int main()
{
    int vet[10], num, busca = false, busca2;

    for (int i=0; i<10; i++)
    {
        scanf ("%i", &vet[i]);
    }

    putchar ('\n');
    scanf ("%i", &num);

    for (int i=0; i<10; i++)
    {
        for (int j=0; j<10; j++)
        {
            if (j != i)
            {
                if ((vet[i] * vet[j]) == num)
                {
                    printf ("\n%i * %i = %i", vet[i], vet[j], num);
                    busca = true;
                }
            }
        }
    }

    if (busca == false)
    {
        printf ("\nNão existe números\n\n");
    }

    if (busca == true)
    {
        printf ("\n\n");
    }

    return 0;
}