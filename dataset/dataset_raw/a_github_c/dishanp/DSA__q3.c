
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

int *add(int A[], int B[], int n, int m)
{
    int max;
    if(m>n)
        max = m;
    else
        max = n;
    int *sum = (int*)malloc(max*sizeof(int));

    for (int i = 0; i<n; i++)
        sum[i] = A[i];

    for (int i=0; i<m; i++)
        sum[i] += B[i];

    printPoly(sum, max);
    return sum;
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

    printf("\nSum of P1 and P2 : ");
    int *sum = add(A, B, n, m);
}