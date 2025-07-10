#include<stdio.h>
#include<string.h>
#include<malloc.h>
int r,c;
void Display(int **mat3)
    {
    int i,j;
    for(i=0;i<r;i++)
        {
        for(j=0;j<c;j++)
            printf("%-3d ",mat3[i][j]);
        printf("\n");
        }
    }
int **Sum(int **mat1,int **mat2,int **mat3)
    {
    int i,j;
    for(i=0;i<r;i++)
        {
        for(j=0;j<c;j++)
            {
            mat3[i][j]=mat1[i][j]+mat2[i][j];
            }
        }
    return mat3;
    }
int main()
    {
        int i,j,m,n;
        int **mat1,**mat2,**mat3;
        printf("Enter the row & col. of the first matrix ");
        scanf("%d%d",&r,&c);
        printf("Enter the row & col. of the second matrix ");
        scanf("%d%d",&m,&n);
        if((r==m)&&(c==n))
            {
                mat1=(int **)malloc(r*sizeof(int *));       
                                                
                mat2=(int **)malloc(r*sizeof(int *));
            
                mat3=(int **)malloc(r*sizeof(int *));       
        
                for(i=0;i<r;i++)
                mat1[i]=(int *)malloc(c*sizeof(int));   
            
                for(j=0;j<r;j++)
                mat2[j]=(int *)malloc(c*sizeof(int));
        
                for(j=0;j<r;j++)
                mat3[j]=(int *)malloc(c*sizeof(int));
        
                printf("\n Enter the first matrix ");
                for(i=0;i<r;i++)
                    {
                    for(j=0;j<c;j++)
                    scanf("%d",&mat1[i][j]);
                    }
                printf("\n Enter the second matrix");
                for(i=0;i<r;i++)
                    {
                    for(j=0;j<c;j++)
                    scanf("%d",&mat2[i][j]);
                    }
        
                Sum(mat1,mat2,mat3);
                
                printf("\n The Resultant matrix is \n");
                Display(mat3);
                
                free(mat1);
                free(mat2);
                free(mat3);
                }
        else
        printf("Please enter same row & col of the two matrix ...");
    return 0;
    }   

