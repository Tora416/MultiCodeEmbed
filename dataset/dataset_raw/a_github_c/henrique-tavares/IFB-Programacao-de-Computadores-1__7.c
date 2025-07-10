#include <stdio.h>
#include <stdlib.h>

long int ackermann(int m, int n)
{
    if (m == 0) return n+1;

    else if (n == 0) return ackermann(m-1, 1);

    else return ackermann(m-1, ackermann(m, n-1));
}

int main()
{
    int m, n;

    do
    {
        printf("\nFunção de Ackermann:\n");
        printf("\t-> m: ");
        scanf("%i", &m);
        getchar();
        printf("\t-> n: ");
        scanf("%i", &n);
        getchar();
        system("clear");

    } while (n < 0 || m < 0);

    printf("\nA(%i,%i) = %li\n\n", m, n, ackermann(m,n));

    return 0;
}