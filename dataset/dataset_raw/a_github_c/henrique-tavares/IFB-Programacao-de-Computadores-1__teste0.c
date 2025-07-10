#include <stdio.h>
#define true 1
#define false 0

int main()
{
    int n, primos[10000], aux = 3, k = 0, primo;
    primos[0] = 2;

    scanf("%i", &n);

    for (int i=0; i< n; i++)
    {
        primo = true;
        for (int j=k; j>=0; j--)
        {
            if ((aux % primos[j]) == 0)
            {
                primo = false;
            }
        }

        if (primo == false)
        {
            aux+=2;
        }

        if (primo == true)
        {
            primos[k+1] = aux;
            k++;
        }
    }

    for (int i=0; i<=k; i++)
    {
        printf("%i ", primos[i]);
    }

    return 0;
}