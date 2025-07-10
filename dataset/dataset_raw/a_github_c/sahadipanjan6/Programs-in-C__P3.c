

#include<stdio.h>
int isSparse(int arr[10][10], int rows, int cols);

void main()
{
    int arr[10][10];
    int rows=0;
    int columns=0;
    int i=0;
    int j=0;
    
    printf("Enter number of rows: \n");
    scanf("%d", &rows);
    printf("Enter number of columns: \n");
    scanf("%d", &columns);
    
    printf("Enter the array elements...\n");
    for(i=0; i<rows; i++)
    {
        for(j=0; j<columns; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    
    if(isSparse(arr, rows, columns) == 1)
        printf("Given Matrix is a SPARSE MATRIX...\n");
    else
        printf("Given Matrix is NOT a SPARSE MATRIX...\n");
        
}

int isSparse(int arr[10][10], int rows, int cols)
{
    int count=0;
    int i=0;
    int j=0;
    
    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++)
        {
            if(arr[i][j] == 0)
                count++;
            else
                continue;
        }
    }
    
    if(count > (rows*cols))
        return 1;
    else
        return 0;
}
