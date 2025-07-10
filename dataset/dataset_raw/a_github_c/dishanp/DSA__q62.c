
#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
void rowsort(int **mat, int m, int n)
{
    for (int i = 0 ; i < m ; i++)
    {
        for (int j = 0 ; j < n - 1 ; j++)
        {
            for (int k = j + 1 ; k < n ; k++)
            {
                if (mat[i][j] > mat[i][k])
                swap(&mat[i][j], &mat[i][k]);
            }
        }
    }
}
void colsort(int **mat, int m , int n)
{
    for (int j = 0 ; j < n ; j++)
    {
        for (int i = 0 ; i < m - 1 ; i++)
        {
            for (int k = i + 1 ; k < m ; k++)
            {
                if (mat[i][j] < mat[k][j])
                swap(&mat[i][j], &mat[k][j]);
            }
        }
    }
}
int main()
{
    int m, n;
    printf("Enter number of rows : ");
    scanf("%d", &m);
    printf("Enter number of columns : ");
    scanf("%d", &n);

    int **mat ;
    mat = (int**)malloc(m*sizeof(int*));
    for(int i = 0 ; i < m ; i++)
    {
        mat[i] = (int*)malloc(n*sizeof(int));
    }
    for(int i = 0 ; i < m ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            printf("Enter element at row %d, column %d : ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }
    printf("Before sorting : \n");
    for(int i = 0 ; i < m ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    rowsort(mat, m ,n);
    printf("After Sorting Rows : \n");
    for(int i = 0 ; i < m ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    colsort(mat, m, n);
    printf("After Sorting Columns : \n");
    for(int i = 0 ; i < m ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}
