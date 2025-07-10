#include<stdio.h>
int SumLowerTri(int mat[][20],int r)
    {
    int i,j,sum=0;
    for(i=0;i<r;i++) 
        {
        for(j=0;j<r;j++) 
            {
            if(i>=j)
                sum=sum+mat[i][j];
            }
        }
    return sum;
    }

int main()
    {
    int i,j,r,c,mat1[20][20];
    printf("Enter the row & col. for the matrix");
    scanf("%d%d",&r,&c);
    
    if(r!=c)
        printf("Lower triangualr matrix or not matrix should be square");
    else
        {
        printf("\n Enter the matrix \n");
        for(i=0;i<r;i++)
        for(j=0;j<c;j++)                
        scanf("%d",&mat1[i][j]);
        
        printf("The sum of the lower triangular matrix=%d",SumLowerTri(mat1,r));    
        }
    return 0;
    }   


