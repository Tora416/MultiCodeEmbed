#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rowNum;
    printf("Enter no. of rows:");
    scanf("%d", &rowNum);

    int **table = calloc(rowNum, sizeof(int*));

    int total = 0;

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

        total += colSize;
    }

    int temp[total];
    int k = 0;

    for(int i = 1 ; i <= table[rowNum - 1][0] ; i++) 
        temp[k++] = table[rowNum - 1][i];

    for(int a = 0 ; a < rowNum - 1 ; a++)
    {
        int colSize = table[a][0];

        for(int i = 1 ; i <= colSize ; i++)
            temp[k++] = table[a][i];
    }

    for(int i = 0 ; i < rowNum - 1; i++)
        table[i][0] = 0;

    table[rowNum - 1] = malloc((total + 1) * sizeof(int));
    table[rowNum - 1][0] = total;

    for(int i = 1; i <= total; i++)
        table[rowNum - 1][i] = temp[i - 1];


    for(int i = 0 ; i < rowNum ; i++)
    {
        int colSize = table[i][0];

        if(colSize == 0)
        {
            printf("NULL\n");
            continue;
        }

        for(int j = 0 ; j <= colSize ; j++)
            printf("%d\t", table[i][j]);

        printf("\n");

        free(table[i]);
    }

    free(table);
}