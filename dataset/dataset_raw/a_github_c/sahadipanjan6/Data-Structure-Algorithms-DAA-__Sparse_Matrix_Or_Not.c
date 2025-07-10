#include<stdio.h>

const int R = 3;
const int C = 3;


void display(int matrix[R][C]);
int check_sparse(int matrix[R][C]);

void main()
{
    int i, j = 0;
    int input_matrix[R][C];

    printf("\nEnter elements of input matrix...\n");
    for(i=0; i<R; i++)
    {
        for(j=0; j<C; j++)
        {
            scanf("%d", &input_matrix[i][j]);
        }
    }

    
    printf("\nOriginal Matrix is a follows:- \n");
    display(input_matrix);

    
    if(check_sparse(input_matrix) == 1)
        printf("\nIt is a Sparse Matrix...\n");
    else
        printf("\nIt is not a Sparse Matrix...\n");
}


void display(int matrix[R][C])
{
    int i, j = 0;
    int rows = R;
    int columns = C;

    for(i=0; i<rows; i++)
    {
        for(j=0; j<columns; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}


int check_sparse(int matrix[R][C])
{
    int i, j, output = 0;
    int size, count_zeros = 0;
    int rows = R;
    int columns = C;

    for(i=0; i<rows; i++)
    {
        for(j=0; j<columns; j++)
        {
            if(matrix[i][j] == 0)
                count_zeros++;
            else
                continue;
        }
    }

    
    size = rows * columns;
    if(count_zeros > (size/2))
        output = 1;

    return output;
}