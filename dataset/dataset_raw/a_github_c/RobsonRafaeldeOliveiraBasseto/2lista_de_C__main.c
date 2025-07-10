#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    int b;

    printf("Escolha um prato:\n\n");
    printf("---------------------------\n");
    printf("1 - Lazanha\n");
    printf("2 - Macarronada\n");
    printf("3 - Strogonff\n");
    printf("4 - Churrasco\n");
    printf("5 - Sair\n");
    printf("---------------------------\n\n");

    printf("Digite o prato: ");
    scanf("%d",&a);

    while(a<=4)
    {
        printf("Escolha um prato:\n\n");
    printf("---------------------------\n");
    printf("1 - Lazanha\n");
    printf("2 - Macarronada\n");
    printf("3 - Strogonff\n");
    printf("4 - Churrasco\n");
    printf("5 - Sair\n");
    printf("---------------------------\n\n");

    printf("Digite o prato: ");
    scanf("%d",&a);
    }
}
