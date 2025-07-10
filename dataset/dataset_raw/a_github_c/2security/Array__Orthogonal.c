
#include<stdio.h>
#include<malloc.h>
#include<math.h>
int IsIdentity(int **mat,int r,int c);
int **Transpose(int **mat1,int **mat2,int r,int c);
int **MultiMat(int **mat1,int **mat2,int **temp,int r,int c,int n);
int main()
    {
    int i,j,r,c,**mat1,**mat2,**temp;
    printf("Enter the row & col. for the matrix");
    scanf("%d%d",&r,&c);
    mat1=(int **)malloc(r*sizeof(int *));   
    mat2=(int **)malloc(r*sizeof(int *));   
    temp=(int **)malloc(r*sizeof(int *));                                       
    
    for(i=0;i<r;i++)
        mat1[i]=(int *)malloc(c*sizeof(int ));
        
    for(i=0;i<r;i++)
        mat2[i]=(int *)malloc(c*sizeof(int ));
    
    for(i=0;i<r;i++)
        temp[i]=(int *)malloc(c*sizeof(int ));
            

    printf("\n Enter the matrix \n");
    for(i=0;i<r;i++)
    for(j=0;j<c;j++)                
    scanf("%d",&mat1[i][j]);
    
    Transpose(mat1,mat2,r,c);
    MultiMat(mat1,mat2,temp,r,c,c);
    
    if(IsIdentity(temp,r,c))
        printf("\nOrthogonal matrix");
    else
        printf("Matrix is not orthogonal matrix");
        
    return 0;
    }
int ** Transpose(int **mat1,int **mat2,int r,int c)
    {
    int i,j;
    for(i=0;i<r;i++)
    for(j=0;j<c;j++)
        mat2[i][j]=mat1[j][i];
    return mat2;
    }
int ** MultiMat(int **mat1,int **mat2,int **temp,int r,int c,int n)
    {
    int i,j,k;
        
        for(i=0;i<r;i++)
            {
            for(j=0;j<n;j++)
                {
                temp[i][j]=0;
                for(k=0;k<c;k++)
                    temp[i][j]+=mat1[i][k]*mat2[k][j];
                }
            }
        return temp;
        }
int IsIdentity(int **mat,int r,int c)
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
