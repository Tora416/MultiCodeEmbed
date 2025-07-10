#include<stdio.h>
#include<malloc.h>
void displayMat(float **mat,int r,int c);
float deterMat(float **mat,int r,int c);
int main()
    {
    int i,j,r,c;
    float **mat,temp;
    printf("Enter the row & col. of the matrix ");
    scanf("%d%d",&r,&c);
    
    if(r!=c)
        printf("For determinant matrix should be square");
    else
        {
        mat=(float **)malloc(r*sizeof(float *));        
                                                
        for(i=0;i<r;i++)
            mat[i]=(float *)malloc(c*sizeof(float));    
    
        printf("\n Enter the matrix \n");
        for(i=0;i<r;i++)
        for(j=0;j<c;j++)
        scanf("%f",&mat[i][j]);
            
        printf("The matrix is:\n");
        displayMat(mat,r,c);
    
        temp=deterMat(mat,r,c);
        
        printf("Determinant of the matrix is:= %f\n", temp);
        }
    return 0;
    }   
void displayMat(float **mat,int r,int c)
    {
    int i,j;
    for(i=0;i<r;i++)
        {
        for(j=0;j<c;j++)
        printf("%f ",mat[i][j]);
        printf("\n");
        }
    }
float deterMat(float **mat,int r,int c)
    {
    int i,j,k;
    float det,ratio;
    for(i = 0; i < r; i++)
        {
            for(j = 0; j < c; j++)
                {
                    if(j>i)
                        {
                        ratio = mat[j][i]/mat[i][i];
                        for(k = 0; k < r; k++)
                                mat[j][k] -= ratio * mat[i][k];
                        }
                }
            }
        det = 1; 
        for(i = 0; i < r; i++)
            det *= mat[i][i];
        return det;
        }
    

