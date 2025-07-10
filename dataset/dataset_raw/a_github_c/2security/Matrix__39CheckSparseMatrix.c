#include<stdio.h>
int count=0;
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
int CheckSparse(int mat[][20],int r,int c)
    {
    int i,j;
    for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
                {
                    if(mat[i][j]==0)
                        count++;
                }
        }
    if(count>=(r*c)/2)
        return 1;
    else
        return 0;   
    }

int main()
    {
    int i,j,r,c,mat[20][20];
    printf("Enter the row & col. of the matrix ");
    scanf("%d%d",&r,&c);    
                    
    printf("\n Enter the matrix \n");
    for(i=0;i<r;i++)
    for(j=0;j<c;j++)
    scanf("%d",&mat[i][j]);
        
    printf("The matrix is:\n");
    displayMat(mat,r,c);
    
    if(CheckSparse(mat,r,c)==1)
        printf("The matrix is sparse matrix\n");
    else
        printf("The matrix is not sparse matrix\n");
    return 0;
    }   



