
#include<stdio.h>
#include<malloc.h>
#include<math.h>
void displayMat(int **mat,int r,int c);
int traceMat(int **mat,int r,int c);

int main()
    {
    int i,j,r,c,**mat,sum=0;
    printf("Enter the row & col. of the matrix ");
    scanf("%d%d",&r,&c);
    
    if(r!=c)
        printf("For determinant matrix should be square");
    else
        {
        mat=(int **)malloc(r*sizeof(int *));        
                                                
        for(i=0;i<r;i++)
            mat[i]=(int *)malloc(c*sizeof(int ));   
    
        printf("\n Enter the matrix \n");
        for(i=0;i<r;i++)
            {
            for(j=0;j<c;j++)
                {
                scanf("%d",&mat[i][j]);
                sum=sum+mat[i][j]*mat[i][j];
                
                }
            }
            
        printf("The matrix is:\n");
        displayMat(mat,r,c);
    
        printf("\nTrace of the matrix is= %d",traceMat(mat,r,c));

        printf("\nNorm of the matrix is=%f",sqrt((double)sum));
        
        }
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
int traceMat(int **mat,int r,int c)
    {
    int i,t=0;
    for(i=0;i<r;i++)
        t=t+mat[i][i];
    return t;
    }
    
