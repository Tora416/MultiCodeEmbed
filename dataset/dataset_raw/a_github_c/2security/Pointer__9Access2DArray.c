#include<stdio.h>
#include<malloc.h>
void Display(int **a,int m,int n)
    {
        int i,j;
        for(i=0;i<m;i++)
            {
                for(j=0;j<n;j++)
                    printf("%d ",*(*(a+i)+j));
                printf("\n");
            }
    }

int main()
    {
        int **a,m,n,i,j,item;
        
        printf("\n Enter row and column of 2D array:: ");
        scanf("%d%d",&m,&n);
        
        a=(int **)malloc(m*sizeof(int **));
        for(i=0;i<m;i++)
            a[i]=(int *)malloc(n*sizeof(int));  
        
        printf("\n Enter %d elements of array::",m*n);
        for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            scanf("%d",(*(a+i)+j));
        
        printf("\n The entered 2D-array is::\n");
        Display(a,m,n);
        
        return 0;
    }
