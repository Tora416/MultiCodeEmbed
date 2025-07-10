

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(void)
{
    int n, i = 0, primo = 0;

    setlocale(LC_ALL, "Portuguese");
    system("color 17");

    printf("Digite o valor de N:  ");
    scanf_s("%i", &n);

    while (i <= n)
    {
        i++;
        if (n % i == 0)
        {
            primo ++;
        }                       
    }

    if (primo == 2)
    {
        printf("%i é um número primo\n", n);
    }
    else
    {
        printf("%i não é um número primo\n\n", n);
    }

    system("pause");
}
