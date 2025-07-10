#include<stdio.h>
void displayMat(int mat[][20],int r,int c)
    {
    int i,j;
    for(i=0;i<r;i++)
        {
        for(j=0;j<c;j++)
        printf("%d ",mat[i][j]);
        printf("\n");
        }
    }
void AddMat(int mat1[][20],int mat2[][20],int r,int c)
    {
    int i,j,temp[20][20];
            
    for(i=0;i<r;i++)
        {
        for(j=0;j<c;j++)
            temp[i][j]=mat1[i][j]+mat2[i][j];
        }
    displayMat(temp,r,c);
    }
int main()
    {
    int i,j,r,c,mat1[20][20],mat2[20][20];
    printf("\n Enter the row & col. for two matrix(Both should be same)");
    scanf("%d%d",&r,&c);
    
    if(r!=c)
        printf("\n For Addition matrix should be square");
    else
        {       
        printf("\n Enter the first matrix \n");
        for(i=0;i<r;i++)
        for(j=0;j<c;j++)                
        scanf("%d",&mat1[i][j]);
        
        printf("\n Enter the second matrix \n");
        for(i=0;i<r;i++)
        for(j=0;j<c;j++)                
        scanf("%d",&mat2[i][j]);
        
        printf("\n The addtion of two matrix is:\n");
        AddMat(mat1,mat2,r,c);
        }
    return 0;
    }
