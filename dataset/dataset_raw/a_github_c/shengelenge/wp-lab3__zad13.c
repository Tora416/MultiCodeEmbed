#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

long oblicz(int A[], int n)
{
    long w = A[0];
    for (int i = 1; i <= n ; i++)
    {
        w = w*2 + A[i];
    }
    return w;
}

int main()
{
    int A[MAX];
    long w;
    int n;
    printf("podaj liczbe cyfr wczytywanej liczby binarnej: ");
    scanf("%d", &n);
    printf("Podaj %d cyfr liczby (od lewej): ", n);
    for (int i = 0; i < n; i++)
    {
        printf("A[%d] = ", i);
        scanf("%d", &A[i]);
    }

    w = oblicz(A, n-1);
    printf("Iteracyjnie: wynik = %ld", w);
    printf("(10)");

    return 0;
}