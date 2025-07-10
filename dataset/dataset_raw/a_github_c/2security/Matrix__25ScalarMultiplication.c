#include<stdio.h>
void displayMat(int mat[][20],int r,int c)
    {
    int i,j;
    for(i=0;i<r;i++)
        {
        for(j=0;j<c;j++)
        printf("%-3d ",mat[i][j]);
        printf("\n");
        }
    }
void ScalarProduct(int mat[][20],int r,int c,int s)
    {
    int i,j;
            
    for(i=0;i<r;i++)
        {
        for(j=0;j<c;j++)
            mat[i][j]=s*mat[i][j];
        }
    displayMat(mat,r,c);
    }
int main()
    {
    int i,j,r,c,mat1[20][20],s;
    printf("\n Enter the row & col. for two matrix(Both should be same): ");
    scanf("%d%d",&r,&c);
    
    if(r!=c)
        printf("\n For Addition matrix should be square");
    else
        {       
        printf("\n Enter the first matrix \n");
        for(i=0;i<r;i++)
        for(j=0;j<c;j++)                
        scanf("%d",&mat1[i][j]);
        
        printf("\n Enter the scalar to be multiplied: ");
        scanf("%d",&s);
        
        printf("\n The addtion of two matrix is:\n");
        ScalarProduct(mat1,r,c,s);
        }
    return 0;
    }
