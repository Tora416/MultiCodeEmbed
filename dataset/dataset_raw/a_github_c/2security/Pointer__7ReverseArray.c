#include<stdio.h>
#include<malloc.h>
void Display(int *a,int n)
    {
        int i;
        for(i=0;i<n;i++)
            printf("%d ",*(a+i));
    }
int* Reverse(int *a,int n)
    {
        int i,j=0,*b;
        b=(int *)malloc(n*sizeof(int *));
        for(i=n-1;i>=0;i--)
        {
            *(b+j)=*(a+i);
            j++;
        }       
        return b;
    }
int main()
    {
        int *a,m,i;
        
        printf("\n Enter size of array1:: ");
        scanf("%d",&m);
        
        a=(int *)malloc(m*sizeof(int *));
        
        printf("\n Enter %d elements of array::",m);
        for(i=0;i<m;i++)
            scanf("%d",&a[i]);
            
        printf("\n Before reverse");
        printf("\n Array:");
        Display(a,m);
    
        Reverse(a,m);  
        
        printf("\n After reverse");
        printf("\n Array:");
        Display(Reverse(a,m),m);
        
        return 0;
    }
