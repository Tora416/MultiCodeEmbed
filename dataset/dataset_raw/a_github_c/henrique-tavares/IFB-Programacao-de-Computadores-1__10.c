#include <stdio.h>
#include <stdlib.h>

void palavra_fibonacci(int n)
{
    if (n == 0) putchar('b');

    else if (n == 1) putchar('a');

    else
    {
        palavra_fibonacci(n-1);
        palavra_fibonacci(n-2);
    }
}

int main()
{
    int n;

    do
    {
        printf("\nDigite um inteiro não-negativo: ");
        scanf("%i", &n);
        getchar();
        system("clear");

    } while (n < 0);

    printf("\nA %iª palavra de Fibonacci:\n\n", n);
    palavra_fibonacci(n);
    printf("\n\n");

    return 0;
}