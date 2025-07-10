#include<stdio.h>
int main()
    {
        int mat1[20][20],mat2[20][20],i,j,n,flag=0;
        printf("\nEnter the order of matrix");
        scanf("%d",&n);
        
        printf("\n Enter first matrix");
        for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        scanf("%d",&mat1[i][j]);
        
        printf("\n Enter second matrix");
        for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        scanf("%d",&mat2[i][j]);
        
        for(i=0;i<n;i++)
            {
                for(j=0;j<n;j++)
                    {
                        if(mat1[i][j]!=mat2[i][j])
                        {
                        flag=1;
                        break;  
                        }       
                    }
            }
        if(flag==0)
            printf("\n Two matrix are equal");
        else
            printf("\n Two matrix are different");
        return 0;
    }
