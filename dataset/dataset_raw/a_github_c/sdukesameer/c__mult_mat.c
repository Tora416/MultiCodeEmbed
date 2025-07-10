#include <stdio.h>
#include <stdlib.h>
#define NROWS 10
#define NCOLS  10
int isValidRC(int r,int c)
{
    if(r>NROWS||r<=0)
    {
        printf("ERROR: Number of rows must be 1-10");
        return 0;
    }
    else if(c>NCOLS||c<=0)
    {
        printf("ERROR: Number of columns must be 1-10");
        return 0;
    }
    else
    return 1;
}
void readMat(int mat[NROWS][NCOLS],int r,int c)
{
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
            scanf("%d",&mat[i][j]);
    }
}
void multMat(int r1,int c1,int mat1[][NCOLS],int r2,int c2,int mat2[][NCOLS],int sum[][NCOLS])
{
    if(c1!=r2)
    {
        printf("ERROR: Number of columns in 1st matrix must equal number of rows in 2nd Matrix");
        exit(1);
    }
    else
    {
    for(int i=0;i<r1;i++)
    {
        for(int j=0;j<c2;j++)
        {
            sum[i][j]=0;
        }
    }
    for(int i=0;i<r1;i++)
    {
        for(int j=0;j<c2;j++)
        {
            for(int k=0;k<c1;k++)
            {
                sum[i][j]+=mat1[i][k]*mat2[k][j];
            }
        }
    }
    }
}
void dispMat(int sum[][NCOLS],int r1,int c2)
{
    for(int i=0;i<r1;i++)
    {
        for(int j=0;j<c2;j++)
        {
            printf("%d ",sum[i][j]);
        }
        printf("\n");
    }
}
int main()
{
        int r1, c1, mat1[NROWS][NCOLS],r2, c2, mat2[NROWS][NCOLS],sum[NROWS][NCOLS];
        scanf("%d%d", &r1, &c1);
        if (!isValidRC(r1, c1)) return 1;
        readMat(mat1, r1, c1);
        scanf("%d%d", &r2, &c2);
        if (!isValidRC(r2, c2)) return 1;
        readMat(mat2, r2, c2);
        multMat(r1, c1, mat1, r2, c2, mat2, sum);
        dispMat(sum, r1, c2);
        return 0;
}
