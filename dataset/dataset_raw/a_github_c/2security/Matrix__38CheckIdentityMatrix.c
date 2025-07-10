#include<stdio.h>
int checkIdentity(int mat[][20],int r,int c)
    {
    int i,j;
    for(i=0;i<r;i++)
        {
        for(j=0;j<c;j++)
            {
            if((i!=j)&&(mat[i][j]!=0))
                return 0;
            else if((i==j)&&(mat[i][j])!=1)
                return 0;
            }
        }
    return 1;
    }   
int main()
    {
    int i,j,r,c,mat1[20][20],mat2[20][20];
    printf("Enter the row & col. for the matrix");
    scanf("%d%d",&r,&c);

    printf("\n Enter the matrix \n");
    for(i=0;i<r;i++)
    for(j=0;j<c;j++)                
    scanf("%d",&mat1[i][j]);
        
    if(checkIdentity(mat1,r,c)==1)
        printf("Matrix is identity matrix of order %d",r);
    else
        printf("Matrix is not identity matrix");
        
    return 0;
    }


