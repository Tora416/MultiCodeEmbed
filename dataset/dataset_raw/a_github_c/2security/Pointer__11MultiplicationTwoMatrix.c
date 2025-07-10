#include<stdio.h>
#include<string.h>
#include<malloc.h>
int r,c,m,n;
void Display(int **mat3)
    {
    int i,j;
    for(i=0;i<r;i++)
        {
        for(j=0;j<n;j++)
            printf("%-3d ",mat3[i][j]);
        printf("\n");
        }
    }
int **Product(int **mat1,int **mat2,int **mat3)
    {
    int i,j,k;
    for(i=0;i<r;i++)
        {
        for(j=0;j<n;j++)
                {
                mat3[i][j]=0;
                for(k=0;k<c;k++)
                    mat3[i][j]+=mat1[i][k]*mat2[k][j];
                }
        }
    return mat3;
    }
int main()
    {
        int i,j;
        int **mat1,**mat2,**mat3;
        printf("Enter the row & col. of the first matrix ");
        scanf("%d%d",&r,&c);
        printf("Enter the row & col. of the second matrix ");
        scanf("%d%d",&m,&n);
        if(c==m)
            {
                mat1=(int **)malloc(r*sizeof(int *));       
                                                
                mat2=(int **)malloc(m*sizeof(int *));
            
                mat3=(int **)malloc(r*sizeof(int *));       
        
                for(i=0;i<r;i++)
                mat1[i]=(int *)malloc(c*sizeof(int));   
            
                for(j=0;j<m;j++)
                mat2[j]=(int *)malloc(n*sizeof(int));
        
                for(j=0;j<r;j++)
                mat3[j]=(int *)malloc(n*sizeof(int));
        
                printf("\n Enter the first matrix ");
                for(i=0;i<r;i++)
                    {
                    for(j=0;j<c;j++)
                    scanf("%d",&mat1[i][j]);
                    }
                printf("\n Enter the second matrix");
                for(i=0;i<m;i++)
                    {
                    for(j=0;j<n;j++)
                    scanf("%d",&mat2[i][j]);
                    }
        
                Product(mat1,mat2,mat3);
                
                printf("\n The Resultant matrix is \n");
                Display(mat3);
                
                free(mat1);
                free(mat2);
                free(mat3);
                }
        else
        printf("OOPS!!Multiplication not possible..");
    return 0;
    }   

