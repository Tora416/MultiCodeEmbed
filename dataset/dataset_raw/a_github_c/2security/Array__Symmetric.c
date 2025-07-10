
#include<stdio.h>
#include<malloc.h>
int **Transpose(int **mat1,int **mat2,int r,int c);
int IsSymmetric(int **mat1,int **mat2,int r,int c);
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
    
    if(IsSymmetric(mat1,Transpose(mat1,mat2,r,c),r,c))
        printf("\nSymmetric matrix");
    else
        printf("\nMatrix is not Symmetric matrix");
        
    return 0;
    }
int IsSymmetric(int **mat1,int **mat2,int r,int c)
    {
    int i,j;
    for(i=0;i<r;i++)
        {
        for(j=0;j<c;j++)
            {
            if(mat1[i][j]!=mat2[i][j])
                return 0;
            }
        }
    return 1;
    }
int ** Transpose(int **mat1,int **mat2,int r,int c)
    {
    int i,j;
    for(i=0;i<r;i++)
    for(j=0;j<c;j++)
        mat2[i][j]=mat1[j][i];
    return mat2;
    }
