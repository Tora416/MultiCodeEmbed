#include <stdio.h>
typedef enum { false, true } bool;

bool czy_pierwsza(int n)
{
    if (n <2)
        return false;

    for (int i = 2; i*i <= n ; i++) {
        if (n % i == 0)
            return false;
    }

    return true;
}

int main()
{
    unsigned int n;

    printf("Podaj liczbe naturlana: ");
    scanf("%d", &n);

    if (czy_pierwsza(n))
        printf("Liczba %u jest pierwsza.\n", n);
    else
        printf("Liczba %u nie jest pierwsza.\n", n);

    return 0;
}