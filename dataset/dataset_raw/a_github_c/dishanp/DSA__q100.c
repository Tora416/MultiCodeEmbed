
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m, n;
    printf("Enter number of rows (m) : ");
    scanf("%d", &m);
    printf("Enter number of columns (n) : ");
    scanf("%d", &n);
    int **mat;
    mat = (int**)malloc(m*sizeof(int*));
    for(int i = 0 ; i < n ; i++)
    {
        mat[i] = malloc(n*sizeof(int));
    }

    for(int i = 0 ; i < m ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            printf("Enter element at row %d, column %d : ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }
    printf("Before swapping : \n");
    for(int i = 0 ; i < m ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    int f = 0;
    int l = n - 1;
    int temp;
    while(f < l)
    {
        for(int i = 0; i < m ; i++)
        {
            temp = mat[i][f];
            mat[i][f] = mat[i][l];
            mat[i][l] = temp;
        }
        f++;
        l--;
    }

    printf("After Swapping : \n");
    for(int i = 0 ; i < m ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }


}