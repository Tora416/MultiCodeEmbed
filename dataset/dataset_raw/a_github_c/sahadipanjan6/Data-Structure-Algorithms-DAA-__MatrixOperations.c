#include<stdio.h>

const int R = 3;
const int C = 3;


void add_matrices(int m1[R][C], int m2[R][C]);
void subtract_matrices(int m1[R][C], int m2[R][C]);
void multiply_matrices(int m1[R][C], int m2[R][C]);
void display_matrix(int matrix[R][C]);

void main()
{
    int i, j = 0;
    int choice = 0;
    int contin = 0;

    int matrix1[R][C];
    int matrix2[R][C];
    int matrix3[R][C];

    
    printf("\nEnter elements of Matrix1...\n");
    for(i=0; i<R; i++)
    {
        for(j=0; j<C; j++)
        {
            scanf("%d", &matrix1[i][j]);
        }
    }
    printf("\nEnter elements of Matrix2...\n");
    for(i=0; i<R; i++)
    {
        for(j=0; j<C; j++)
        {
            scanf("%d", &matrix2[i][j]);
        }
    }

    do
    {
        printf("\nPress:- ");
        printf("\n1 for ADDITION");
        printf("\n2 for SUBTRACTION");
        printf("\n3 for  MULTIPLICATION");
        printf("\n4 for EXIT");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                add_matrices(matrix1, matrix2);
                break;

            case 2:
                subtract_matrices(matrix1, matrix2);
                break;

            case 3:
                multiply_matrices(matrix1, matrix2);
                break;

            case 4:
                exit(0);
                break;

            default:
                printf("\nEnter a correct choice...");
        }
        printf("\nPress 5 to continue, else press any other number: ");
        scanf("%d", &contin);
    }while(contin == 5);
}


void add_matrices(int m1[R][C], int m2[R][C])
{
    int i, j = 0;
    int output[R][C];

    for(i=0; i<R; i++)
    {
        for(j=0; j<C; j++)
        {
            output[i][j] = m1[i][j] + m2[i][j];
        }
    }

    
    printf("\nResultant Matrix after ADDITION:- \n");
    display_matrix(output);
}


void subtract_matrices(int m1[R][C], int m2[R][C])
{
    int i, j = 0;
    int output[R][C];

    for(i=0; i<R; i++)
    {
        for(j=0; j<C; j++)
        {
            output[i][j] = m1[i][j] - m2[i][j];
        }
    }

    
    printf("\nResultant Matrix after SUBTRACTION:- \n");
    display_matrix(output);
}


void multiply_matrices(int m1[R][C], int m2[R][C])
{
    int i, j, k = 0;
    int sum = 0;
    int output[R][C];

    for(i=0; i<R; i++)
    {
        for(j=0; j<C; j++)
        {
            for(k=0; k<R; k++)
            {
                sum += m1[i][k] * m2[k][j];
            }
            output[i][j] = sum;
            sum = 0;
        }
    }

    
    printf("\nResultant Matrix after MULTIPLICATION:- \n");
    display_matrix(output);
}


void display_matrix(int matrix[R][C])
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