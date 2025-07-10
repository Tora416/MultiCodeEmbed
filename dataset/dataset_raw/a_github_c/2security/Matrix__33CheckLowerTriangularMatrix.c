#include<stdio.h>
int checkLowerTri(int mat[][20],int r)
    {
    int i,j;
    for(i=0;i<r-1;i++) 
        {
        for(j=1;j<r;j++) 
            {
            if(i<j && mat[i][j]!=0)
                {
                return 0;
                break;  
                }           
            }
        }
    return 1;
    }

int main()
    {
    int i,j,r,c,mat1[20][20];
    printf("Enter the row & col. for the matrix");
    scanf("%d%d",&r,&c);
    
    if(r!=c)
        printf("For checking Lower triangualr matrix or not matrix should be square");
    else
        {
        printf("\n Enter the matrix \n");
        for(i=0;i<r;i++)
        for(j=0;j<c;j++)                
        scanf("%d",&mat1[i][j]);
        
        if(checkLowerTri(mat1,r)==1)
            printf("Matrix is Lower triangualr matrix");
        else
            printf("Matrix is not Lower triangualr matrix");
        }
    return 0;
    }   


