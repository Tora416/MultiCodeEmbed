#include<stdio.h>
#include<stdlib.h>

void multiply(int **arr1, int **arr2, int m, int n, int p, int q, int **product)
{
    int sum = 0;

    for(int c = 0 ; c < m ; c++)
        for(int d  = 0 ; d < q; d++)
        {
            for(int k = 0 ; k < p ; k++)
                sum += arr1[c][k] * arr2[k][d];

            product[c][d] = sum;
            sum = 0;
        }
}

int main()
{
    int m, n, p, q;

    printf("Enter dimensions of first array:");
    scanf("%d %d", &m, &n);

    int **arr1 = calloc(m, sizeof(int*));

    for(int i = 0 ; i < m ; i++)
        arr1[i] = calloc(n, sizeof(int));

    for(int i = 0 ; i < m; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &arr1[i][j]);

    printf("Enter dimensions of second array:");
    scanf("%d %d", &p, &q);

    int **arr2 = calloc(p, sizeof(int*));

    for(int i = 0 ; i < p ; i++)
        arr2[i] = calloc(q, sizeof(int));

    for(int i = 0 ; i < p; i++)
        for(int j = 0; j < q; j++)
            scanf("%d", &arr2[i][j]);

    if(n != p)
    {
        printf("Invalid Order");
        return 0;
    }

    else if (n == p)
    {
        int **product = calloc(m, sizeof(int*));

        for(int i = 0 ; i < m ; i++)
            product[i] = calloc(q, sizeof(int));

        multiply(arr1, arr2, m, n, p, q, product);

        printf("Product: \n");

        for(int i = 0 ; i < m ; i++)
        {
            for(int j = 0; j < q ; j++)
                printf("%d \t", product[i][j]);

            printf("\n");
        }

    }

}