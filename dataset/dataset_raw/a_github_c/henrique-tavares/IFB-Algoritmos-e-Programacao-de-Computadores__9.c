#include <stdio.h>
#include <stdlib.h>

int main()
{
    system("clear");

    int n;
    float saldo = 1000, x, y;

    printf("########################\n");
    printf("# 1 - Saque            #\n");
    printf("# 2 - Depósito         #\n");
    printf("# 3 - Sair do programa #\n");
    printf("########################\n");
    printf("Saldo: R$%.2f\n", saldo);
    printf("Faça sua escolha: ");

    scanf("%i", &n);

    system("clear");

    while (n != 3)
    {
        system("clear");

        switch (n)
        {
        case 1:
            printf("SAQUE:\n");
            printf("\nDigite quantos reais deseja sacar: ");
            scanf("%f", &x);

            saldo = saldo - x;

            break;

        case 2:
            system("clear");

            printf("DEPÓSITO:\n");
            printf("\nDigite quantos reais deseja depositar: ");
            scanf("%f", &y);

            saldo = saldo + y;

            break;
        }

        system("clear");

        printf("########################\n");
        printf("# 1 - Saque            #\n");
        printf("# 2 - Depósito         #\n");
        printf("# 3 - Sair do programa #\n");
        printf("########################\n");
        printf("Saldo: R$%.2f\n", saldo);
        printf("Faça sua escolha: ");

        scanf("%i", &n);
    }

    printf("\n");
    return 0;
}