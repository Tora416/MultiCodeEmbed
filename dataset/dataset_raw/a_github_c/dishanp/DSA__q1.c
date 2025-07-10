
#include <stdio.h>
#include <stdlib.h>
int num = 0;
int** readmatrix(int **A, int m, int n)
{
    A = (int**)malloc(m * sizeof(int*));
    num = 0;
    for(int i = 0 ; i < m ; i++)
    {
         A[i] = (int*)malloc(n * sizeof(int));
    }
    printf("Enter elements : \n");
    for (int i = 0 ; i < m ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            scanf("%d", &A[i][j]);
            if(A[i][j] != 0)
                num++;
        }
    }
    return A;
}
int** createsparserow(int **p, int m, int n)
{
    int r = num + 1;
    int **sparse = (int**)malloc(r * sizeof(int*));
    for(int i = 0 ; i < r ; i++)
    {
        sparse[i] = (int*)malloc(3 * sizeof(int));
    }
    sparse[0][0] = m;
    sparse[0][1] = n;
    sparse[0][2] = num;

    int k = 1;
    for(int i = 0 ; i < m ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            if(p[i][j] != 0)
            {
                sparse[k][0] = i;
                sparse[k][1] = j;
                sparse[k][2] = p[i][j];
                k++;
            }
        }
    }
    return sparse;
}

int** createsparsecol(int **p, int m, int n)
{
    int c = num + 1;
    int **sparse = (int**)malloc(3 * sizeof(int*));
    for(int i = 0 ; i < 3 ; i++)
    {
        sparse[i] = (int*)malloc(c * sizeof(int));
    }
    sparse[0][0] = m;
    sparse[1][0] = n;
    sparse[2][0] = num;

    int k = 1;
    for(int i = 0 ; i < m ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            if(p[i][j] != 0)
            {
                sparse[0][k] = i;
                sparse[1][k] = j;
                sparse[2][k] = p[i][j];
                k++;
            }
        }
    }
    return sparse;
}

void displayrowmajor(int **sp)
{
    printf("\nRow Major Representation : \n\n");
    printf("\tRows\t\tColumns\t\tValues\n");
    for(int i = 0 ; i < num + 1 ; i++)
    {
        for(int j = 0 ; j < 3 ; j++)
        {
            printf("\t%d\t", sp[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void displaycolmajor(int **sp)
{
    printf("\nColumn Major Representation : \n\n");
    for(int i = 0 ; i < 3 ; i++)
    {
        for(int j = -1 ; j < num + 1 ; j++)
        {
            if(i == 0 && j == -1)
                printf("Row\t");
            else if(i == 1 && j == -1)
                printf("Col\t");
            else if(i == 2 && j == -1)
                printf("Val\t");
            else
                printf("\t%d\t", sp[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int m, n;
    printf("Enter number of rows and columns : ");
    scanf("%d%d", &m, &n);
    int **A = NULL, **sparserow = NULL, **sparsecol = NULL;
    A = readmatrix(A, m, n);
    sparserow = createsparserow(A, m, n);
    sparsecol = createsparsecol(A, m, n);
    displayrowmajor(sparserow);
    displaycolmajor(sparsecol);
}