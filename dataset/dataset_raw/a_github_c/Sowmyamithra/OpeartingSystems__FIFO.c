
#include<stdio.h>
#include<stdio.h>
#define F 3
int n,i,j,page,Queue[F],f=-1,r=-1,PFR;
void enqueue(int page)
{
    if(f==-1 && r==-1)
    {
        f=f+1;
        r=r+1;
        Queue[r]=page;
    }
    else
    {
        r=(r+1)%3;
        Queue[r]=page;
    }
}
int isthere(int page)
{
    int flag=-1;
    for(j=0;j<3;j++)
    {
        if(Queue[j]==page)
        {
            flag=1;
            break;
        }
    }
    return(flag);
}
void main()
{
    for(i=0;i<3;i++)
        Queue[i]=-1;    
    printf("\nEnter the number of pages : ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("\nEnter the page : ");
        scanf("%d",&page);
        if(isthere(page)==-1)
        {
            enqueue(page);
            PFR=PFR+1;
        }
        printf("\nStatus : ");
        for(j=0;j<3;j++)
            printf("%d\t",Queue[j]);
    }
    printf("\nPage Fault Rate is : %d",PFR);
}