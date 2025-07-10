
#include <stdio.h>
#include <stdlib.h>

void printPoly(int poly[], int n)
{
    for (int i = 0 ; i < n ; i++)
    {
        printf("%d", poly[i]);
        if (i != 0)
            printf("x^%d", i) ;
        if (i != n-1)
            printf(" + ");
    }
    printf("\n");
}

int *multiply(int A[], int B[], int n, int m)
{
    int *prod = (int*)malloc((n + m - 1)*sizeof(int));

    for (int i = 0; i < n + m - 1; i++)
        prod[i] = 0;


    for (int i = 0 ; i < n; i++)
    {
        for (int j = 0 ; j < m ; j++)
            prod[i+j] += A[i]*B[j];
    }

    printPoly(prod, n+m-1);
    return prod;
}

int main()
{
    int n, m;
    printf("Enter number of terms for P1: ");
    scanf("%d", &n);
    int A[n];
    printf("Enter coefficients according to increasing order of exponents : ");
    for(int i = 0 ; i < n ; i++)
        scanf("%d", &A[i]);
    printf("\nFirst polynomial : ");
    printPoly(A, n);

    printf("\nEnter number of terms for P2: ");
    scanf("%d", &m);
    int B[m];
    printf("Enter coefficients according to increasing order of exponents : ");
    for(int i = 0 ; i < m ; i++)
        scanf("%d", &B[i]);
    printf("\nSecond polynomial : ");
    printPoly(B, m);

    printf("\nProduct : ");
    int *prod = multiply(A, B, n, m);

}