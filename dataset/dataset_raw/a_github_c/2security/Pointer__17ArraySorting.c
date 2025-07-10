#include<stdio.h>
#include<malloc.h>

void Mysort(int *a,int n)
    {
    int i,j,temp;
    for(i=0;i<n-1;i++)
        {
        for(j=0;j<n-i-1;j++)
            {
            if(*(a+j)>*(a+j+1)) 
                {
                    temp=*(a+j);
                    *(a+j)=*(a+j+1);
                    *(a+j+1)=temp;
                }
            }
        }
    }
int main()
    {
        int *a,m,i;
        
        printf("\n Enter size of array1:: ");
        scanf("%d",&m);
        
        a=(int *)malloc(m*sizeof(int *));
        
        printf("\n Enter %d elements of array::",m);
        for(i=0;i<m;i++)
            scanf("%d",&*(a+i));
        
        Mysort(a,m);
        
        printf("\n After sorting:: ");
        for(i=0;i<m;i++)
            printf("%d ",*(a+i));
        return 0;
    }
