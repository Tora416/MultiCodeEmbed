#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    fib = 1, pad, cat, quit

} func_t;

void le_numero(int *n)
{
    do
    {
        printf("\nDigite um inteiro positivo: ");
        scanf("%i", n);
        getchar();
        system("clear");

    } while (n < 0);
}

long int fibonacci(int n)
{
    return (n > 1) ? fibonacci(n-1) + fibonacci(n-2) : 1;
}

long int padovan(int n)
{
    return (n > 2) ? padovan(n-2) + padovan(n-3) : 1;
}

long int catalan(float n)
{
    return (n > 0) ? ((4*n - 2) / (n+1)) * catalan(n-1) : 1;
}

int main()
{
    int n;
    func_t escolha;
    
    do
    {
        do
        {
            printf("\t(1) Fibonacci\n");
            printf("\t(2) Padovan\n");
            printf("\t(3) Catalan\n");
            printf("\t(4) Sair\n");
            printf("\n\tDigite sua escolha: ");
            scanf("%i", &escolha);
            getchar();
            system("clear");

        } while (escolha != fib && escolha != pad && escolha != cat && escolha != quit);

        if (escolha == quit) return 0;

        le_numero(&n);

        switch (escolha)
        {
            case fib:
                printf("\nFibonacci de %i = %li\n\n", n, fibonacci(n));
                break;
            
            case pad:
                printf("\nPadovan de %i = %li\n\n", n, padovan(n));
                break;
            
            case cat:
                printf("\nCatalan de %i = %li\n\n", n, catalan(n));
                break;
        }

        printf("\nPressione ENTER para continuar: ");
        getchar();
        system("clear");

    } while (escolha != quit);

    return 0;
}