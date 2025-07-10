
#include<stdio.h>
#include<stdlib.h>
#define F 3
int n,page[100];
int Queue[F],r=-1,f=-1;
int find_pos(int pg,int pos)
{
    int i,set=0;
    for(i=pos;i>=0;i--)
    {
        if(page[i]==pg)
        {
            set=i;
            break;
        }
    }
    return(set);
}
void enqueue(int page,int pos)
{
    int i,new,set=0,min;
    if(r==-1 && f==-1)
    {
        f=f+1;
        r=r+1;
        Queue[r]=page;
    }
    else if(r<2)
    {
        r=r+1;
        Queue[r]=page;
    }
    else
    {
        min=1000;
        for(i=0;i<3;i++)
        {
            new=find_pos(Queue[i],pos-1);
            if(new<min)
            {
                min=new;
                set=i;
            }
        }
        Queue[set]=page;
    }   
}
int isthere(int page)
{
    int i,flag=-1;
    for(i=0;i<3;i++)
    {
        if(Queue[i]==page)
        {
            flag=1;
            break;
        }
    }   
    return(flag);
}
void main()
{
    int i,j,PFR=0;
    for(i=0;i<3;i++)
        Queue[i]=-1;
    printf("\nEnter the number of pages : ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("\nEnter the page : ");
        scanf("%d",&page[i]);
    }
    for(i=0;i<n;i++)
    {
        if(isthere(page[i])==-1)
        {
            enqueue(page[i],i);
            PFR=PFR+1;
        }
        printf("\nStatus : ");
        for(j=0;j<3;j++)
            printf("%d\t",Queue[j]);
    }
    printf("\nPage Fault Rate is : %d",PFR);
}