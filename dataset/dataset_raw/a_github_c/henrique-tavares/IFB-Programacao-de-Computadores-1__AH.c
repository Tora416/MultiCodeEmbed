#include <stdio.h>

int main()
{
    int n, qtd = 0;
    long int vet[1000], aux, aux2;

    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%li", &vet[i]);
        for (int j = i; j > 0; j--)
        {
            if (vet[j] < vet[j - 1])
            {
                aux = vet[j];
                vet[j] = vet[j - 1];
                vet[j - 1] = aux;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            aux2 = vet[i];
            qtd++;
        }

        else if (vet[i] == aux2)
        {
            qtd++;
        }

        else if (vet[i] != aux2)
        {
            printf("%li %i\n", vet[i - 1], qtd);
            qtd = 0;
            aux2 = vet[i];
            qtd++;
        }

        if (i == (n - 1))
        {
            printf("%li %i\n", vet[i], qtd);
        }
    }
    

    return 0;
}