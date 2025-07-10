
#include<stdio.h>
#include<malloc.h>
#include<math.h>
void Transpose(int **mat1,int **mat2,int r,int c);
void displayMat(int **mat,int r,int c);
int main()
    {
    int i,j,r,c,**mat1,**mat2;
    printf("Enter the row & col. for the matrix");
    scanf("%d%d",&r,&c);
    mat1=(int **)malloc(r*sizeof(int *));   
    mat2=(int **)malloc(r*sizeof(int *));                                   
    
    for(i=0;i<r;i++)
        mat1[i]=(int *)malloc(c*sizeof(int ));
        
    for(i=0;i<r;i++)
        mat2[i]=(int *)malloc(c*sizeof(int ));
            

    printf("\n Enter the matrix \n");
    for(i=0;i<r;i++)
    for(j=0;j<c;j++)                
    scanf("%d",&mat1[i][j]);
        
    Transpose(mat1,mat2,r,c);
        
    printf("Transpose of the matrix is:\n");
    displayMat(mat2,r,c);
    return 0;
    }
void displayMat(int **mat,int r,int c)
    {
    int i,j;
    for(i=0;i<r;i++)
        {
        for(j=0;j<c;j++)
        printf("%d ",mat[i][j]);
        printf("\n");
        }
    }   
void Transpose(int **mat1,int **mat2,int r,int c)
    {
    int i,j;
    for(i=0;i<r;i++)
    for(j=0;j<c;j++)
        mat2[i][j]=mat1[j][i];
    }
