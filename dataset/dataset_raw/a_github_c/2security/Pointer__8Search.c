#include<stdio.h>
#include<malloc.h>
void Display(int *a,int n)
    {
        int i;
        for(i=0;i<n;i++)
            printf("%d ",*(a+i));
    }
int Search(int *a,int n,int item)
    {
        int i,j=0,pos=0;
        for(i=0;i<n;i++)
            {
            if(*(a+i)==item)
                {
                    pos=i+1;
                    break;
                }
            }       
        return pos;
    }
int main()
    {
        int *a,m,i,item;
        
        printf("\n Enter size of array1:: ");
        scanf("%d",&m);
        
        a=(int *)malloc(m*sizeof(int *));
        
        printf("\n Enter %d elements of array::",m);
        for(i=0;i<m;i++)
            scanf("%d",&a[i]);
        
        printf("\n Enter the item to found");
        scanf("%d",&item);
        
        i=Search(a,m,item);
        
        if(i==0)
            printf("\n %d is not found",item);
        else
            printf("\n %d is found at position %d",item,i);
    
        return 0;
    }
