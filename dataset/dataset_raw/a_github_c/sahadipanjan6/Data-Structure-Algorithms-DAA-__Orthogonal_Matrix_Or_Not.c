#include<stdio.h>

const int R = 3;
const int C = 3;


void display(int matrix[R][C]);
int check_Identity_Matrix(int matrix[R][C]);

void main()
{
    int i, j, k, temp, sum = 0;
    int rows = R;
    int columns = C;
    int input_matrix[R][C];
    int transposed_matrix[R][C];
    int product_matrix[R][C];
    

    printf("\nEnter the matrix elements...\n");
    for(i=0; i<R; i++)
    {
        for(j=0; j<C; j++)
        {
            scanf("%d", &input_matrix[i][j]);
        }
    }

    
    printf("\nOriginal Matrix is as follows:- \n");
    display(input_matrix);

    
    temp = rows;
    rows = columns;
    columns = rows;

    
    for(i=0; i<rows; i++)
    {
        for(j=0; j<columns; j++)
        {   
            transposed_matrix[i][j] = input_matrix[j][i];
        }
    }

    
    for(i=0; i<R; i++)
    {
        for(j=0; j<C; j++)
        {
            for(k=0; k<R; k++)
            {
                sum += input_matrix[i][k] * transposed_matrix[k][j];
            }
            product_matrix[i][j] = sum;
            sum = 0;
        }
    }

    
    if(check_Identity_Matrix(product_matrix) == 0)
        printf("\nInput Matrix is orthogonal...\n");
    else
        printf("\nInput Matrix is NOT orthogonal...\n");
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


int check_Identity_Matrix(int matrix[R][C])
{
    int i, j, flag, output = 0;
    int rows = R;
    int columns = C;

    for(i=0; i<rows; i++)
    {
        for(j=0; j<columns; j++)
        {
            
            if((i==j) && (matrix[i][j]==1))
                continue;

            else if((i!=j) && (matrix[i][j]==0))
                continue;
            
            else
            {
                flag = 1;
                break;
            }
        }

        
        if(flag == 1)
        {
            output = 1;
            break;
        }
    }

    
    return output;
}