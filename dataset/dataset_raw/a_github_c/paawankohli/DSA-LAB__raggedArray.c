#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rowNum;
    printf("Enter no. of rows:");
    scanf("%d", &rowNum);

    int **table = calloc(rowNum, sizeof(int*));

    for(int i = 0 ; i < rowNum ; i++)
    {
        int colSize;
        printf("Enter no. of columns of %dth row: ", i + 1);
        scanf("%d", &colSize);

        table[i] = calloc(colSize + 1, sizeof(int));

        table[i][0] = colSize;  

        printf("Enter %d elements: ", colSize);
        for(int j = 1 ; j <= table[i][0] ; j++)
            scanf("%d", &table[i][j]);
    }

    for(int i = 0 ; i < rowNum ; i++)
    {
        int colSize = table[i][0];

        for(int j = 1 ; j <= colSize ; j++)
            printf("%d\t", table[i][j]);

        printf("\n");

        free(table[i]);
    }

    free(table);
}