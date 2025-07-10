#include <stdio.h>
#include <stdlib.h>

void le_mdc(int *a, int *b)
{
    do
    {
        printf("\nDigite dois inteiros 'a' e 'b', onde 'b' > 0:\n");
        printf("\t-> a: ");
        scanf("%i", a);
        getchar();
        printf("\t-> b: ");
        scanf("%i", b);
        getchar();
        system("clear");

    } while (b <= 0);
}

void le_mmc(int *a, int *b)
{
    do
    {
        printf("\nDigite dois inteiros não-negativos 'a' e 'b':\n");
        printf("\t-> a: ");
        scanf("%i", a);
        getchar();
        printf("\t-> b: ");
        scanf("%i", b);
        getchar();
        system("clear");
    
    } while (a < 0 || b < 0);
}

int mdc(int a, int b)
{
    return (a % b > 0) ? mdc(b, a % b) : b;
}

int mmc(int a, int b)
{
    return (a == 0 || b == 0) ? 0 : (a*b) / mdc(a,b);
}

int main()
{
    int a, b, escolha;

    do
    {
        do
        {
            printf("\n\t(1) MDC\n");
            printf("\t(2) MMC\n");
            printf("\t(3) Sair\n");
            printf("\tDigite sua escolha: ");
            scanf("%i", &escolha);
            getchar();
            system("clear");
        
        } while (escolha != 1 && escolha != 2 && escolha != 3);

        if (escolha == 3) return 0;

        if (escolha == 1)
        {
            le_mdc(&a, &b);
            printf("\nMDC(%i,%i) = %i\n\n", a, b, mdc(a,b));
        }

        else if (escolha == 2)
        {
            le_mmc(&a, &b);
            printf("\nMMC(%i,%i) = %i\n\n", a, b, mmc(a,b));
        }

        printf("\nPressione ENTER para continuar: ");
        getchar();
        system("clear");
    
    } while (escolha != 3);

    return 0;
}