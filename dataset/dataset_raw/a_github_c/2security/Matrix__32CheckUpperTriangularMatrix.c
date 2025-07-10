#include<stdio.h>
int checkUpperTri(int mat[][20],int r)
    {
    int i,j,flag=1;
    for(i=1;i<r;i++) 
        for(j=0;j<i;j++) 
            if(mat[i][j]!= 0) 
                return 0;
        return 1;
    }

int main()
    {
    int i,j,r,c,mat1[20][20];
    printf("Enter the row & col. for the matrix");
    scanf("%d%d",&r,&c);
    
    if(r!=c)
        printf("For checking upper triangualr matrix or not matrix should be square");
    else
        {
        printf("\n Enter the matrix \n");
        for(i=0;i<r;i++)
        for(j=0;j<c;j++)                
        scanf("%d",&mat1[i][j]);
        
        if(checkUpperTri(mat1,r)==1)
            printf("Matrix is Upper triangualr matrix");
        else
            printf("Matrix is not Upper triangualr matrix");
        }
    return 0;
    }   


