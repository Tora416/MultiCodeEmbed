#include<stdio.h>

const int R = 3;
const int C = 3;


void transpose_and_display(int matrix[R][C]);
void display(int matrix[R][C]);

void main()
{
    int i, j = 0;
    int input_matrix[R][C];
    
    printf("\nEnter the matrix elements...");
    for(i=0; i<R; i++)
    {
        for(j=0; j<C; j++)
        {
            scanf("%d", &input_matrix[i][j]);
        }
    }

    
    printf("\nOriginal Matrix is as follows:- \n");
    display(input_matrix);

    
    transpose_and_display(input_matrix);
}


void transpose_and_display(int matrix[R][C])
{
    int rows = R;
    int columns = C;
    int i, j, temp = 0;
    int output_matrix[R][C];

    
    temp = columns;
    columns = rows;
    rows = temp;

    
    for(i=0; i<rows; i++)
    {
        for(j=0; j<columns; j++)
        {   
            output_matrix[i][j] = matrix[j][i];
        }
    }

    
    printf("\nTransposed Matrix is as follows:- \n");
    display(output_matrix);
}


void display(int matrix[R][C])
{
    int i, j = 0;
    for(i=0; i<R; i++)
    {
        for(j=0; j<C; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}