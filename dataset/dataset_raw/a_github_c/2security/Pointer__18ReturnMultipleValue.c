#include<stdio.h>
#include<malloc.h>

int* Myreturn(int *a,int n)
    {
    int i;
    for(i=0;i<n;i++)
        *(a+i)=2*(*(a+i));

    return a;
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
        
        Myreturn(a,m);
        
        printf("\n Result:: ");
        for(i=0;i<m;i++)
            printf("%d ",*(a+i));
        return 0;
    }
