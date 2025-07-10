

         




#include "sparse_matrix.h"

int main()
{
    int row,column;

    printf("Enter the row value\n");
    scanf("%d",&row);
    printf("Enter the column value\n");
    scanf("%d",&column);

    if(row == 0 | column == 0) {
        printf("Invalid row or column value\n");
        exit(0);
    }
    int sparse_matrix[row][column];

    int i, j, size = 0;
    printf("Enter the values for Sparse matrix\n");

    for(i = 0; i < row; i++ ) {
        for(j = 0; j < column; j++) {
            printf("Enter the value of Row %d\t Column %d\n",i,j);
            scanf("%d",&sparse_matrix[i][j]);
            if(sparse_matrix[i][j] != 0)
                size = size + 1;
        }
    }

    int new_matrix[row][size]; 
    int k = 0;
    for(i = 0; i < row; i++ ) {
        for(j = 0; j < column; j++) {
            if( sparse_matrix[i][j] != 0) {
                new_matrix[0][k] = i;
                new_matrix[1][k] = j;
                new_matrix[2][k] = sparse_matrix[i][j];
                k++;
            }
        }
    }


    for(i = 0; i < row; i++ ) {
        i==0 ? printf("Row   \t") : i==1 ? printf("column\t"):printf("Value \t");
        for(j = 0; j < size; j++) {
            printf("%d ",new_matrix[i][j]);
        }
        printf("\n");
    }
}
