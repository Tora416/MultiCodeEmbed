#include <stdio.h>
#define true 1
#define false 0

long int primos[500];

int primov(long int n)
{
    primos[0] = 2;
    int k = 0, primo;

    for (long int i = 3; (primos[k] * primos[k]) <= n; i += 2)
    {
        primo = true;
        for (int j = 0; (j <= k) && (primo == true); j++)
        {
            if ((i % primos[j]) == 0)
            {
                primo = false;
            }
        }

        if (primo == true)
        {
            primos[k + 1] = i;
            k++;
        }
        
    }

    return k;
}

int busca(long int n, int k)
{
    for (int j = 0; (j <= k) && ((primos[j] * primos[j]) <= n); j++)
    {
        if ((n % primos[j]) == 0)
        {
            printf("composto\n");
            return 0;
        }
    }

    printf("primo\n");
    return 0;
}

int main()
{
    long int num[100000], maior;
    int n, k;

    scanf("%i", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%li", &num[i]);

        if (i == 0)
        {
            maior = num[i];
        }

        else if (num[i] > maior)
        {
            maior = num[i];
        }
    }

    k = primov(maior);

    for (int i = 0; i < n; i++)
    {

        if (num[i] == 1)
        {
            printf("composto\n");
        }

        else if (num[i] == 2)
        {
            printf("primo\n");
        }

        else
        {
            busca(num[i], k);
        }
    }

    

    return 0;
}