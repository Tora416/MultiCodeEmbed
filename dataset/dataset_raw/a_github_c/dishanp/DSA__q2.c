
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m, n;
    printf("Enter dimensions (m,n) : ");
    scanf("%d%d", &m, &n);
    int **p = (int**)malloc(m*sizeof(int*));
    for(int i = 0 ; i < m ; i++)
    {
        p[i] = (int*)malloc(n*sizeof(int));
    }

    printf("Enter elements : \n");
    for(int i = 0 ; i < m ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            scanf("%d", &p[i][j]);
        }
    }

    printf("\nThe matrix : \n");
    for(int i = 0 ; i < m ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}