#include <stdio.h>

long int fib[47];

void fibonacci(int maior)
{
    fib[0] = 1;
    fib[1] = 1;
    
    for (int a = 2; a <= maior; a++)
    {
        fib[a] = fib[a - 1] + fib[a - 2];
    }
}

long int supersigma(int i, int j)
{
    long int soma = 0;

    for (int a = i; a <= j; a++)
    {
        soma += fib[a];
    }

    return soma;
}

int main()
{
    int n, iv[100000], jv[100000], maior = 0;

    scanf("%i", &n);

    for (int a = 0; a < n; a++)
    {
        scanf("%i", &iv[a]);
        scanf("%i", &jv[a]);

        if (jv[a] > maior)
            maior = jv[a];
    }

    fibonacci(maior);

    for (int a=0; a<n; a++)
    {
        printf("%li\n", supersigma(iv[a], jv[a]));
    }

    return 0;
}