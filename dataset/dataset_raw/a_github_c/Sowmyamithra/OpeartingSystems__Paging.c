
#include<stdio.h>
#include<stdlib.h>
int Mem[16],index1;
struct table
{
    int id,size,indices[16];
}t[16];
int get_count()
{
    int i,ct=0;
    for(i=0;i<16;i++)
    {
        if(Mem[i]==0)
            ct=ct+1;
    }
    return(ct);
}
void rem_program(int id1)
{
    int i,k;
    for(i=0;i<16;i++)
    {
        if(Mem[i]==id1)
        {
            Mem[i]=0;
        }
    }
    for(i=0;i<index1;i++)
    {
        if(t[i].id==id1)
            break;
    }
    t[i].id=-1;
    t[i].size=-1;
    for(k=0;k<16;k++)
    {
        if(t[i].indices[k]!=-1)
            t[i].indices[k]=-1;
        else
            break;
    }
}
void add_program(int id,int size)
{
    int ct=get_count();
    int temp=size;
    int i,k,ch=1,id1;
    if(ct>=size)
    {
        k=0;
        for(i=0;i<16 && size>0;i++)
        {
            if(Mem[i]==0)
            {
                Mem[i]=id;
                size=size-1;
                t[index1].indices[k]=i;
                k++;
            }
        }
        t[index1].id=id;
        t[index1].size=temp;
        t[index1].indices[k]=-1;
        index1=index1+1;
    }
    else
    {
        while(ch==1)
        {
            printf("\nIs there any possiblity of removing a program : ");
            scanf("%d",&ch);
            if(ch==1)
            {
                printf("\nEnter program id : ");
                scanf("%d",&id1);
                rem_program(id1);
            }
            else
            {
                break;
            }
        }
        ct=get_count();
        if(ct>=size)
        {
            k=0;
            for(i=0;i<16 && size>0;i++)
            {
                if(Mem[i]==0)
                {
                    Mem[i]=id;
                    size=size-1;
                    t[index1].indices[k]=i;
                    k++;
                }
            }
            t[index1].id=id;
            t[index1].size=temp;
            t[index1].indices[k]=-1;
            index1=index1+1;
        }
        else
            printf("\nNot possible");
    }
}
void display_table()
{
    int i,j;
    printf("\nProgram_id\tsize\tpages\n");
    for(i=0;i<index1;i++)
    {
        printf("\n%d\t%d\t",t[i].id,t[i].size);
        for(j=0;j<16;j++)
        {
            if(t[i].indices[j]!=-1)
            {
                printf("%d ",t[i].indices[j]);
            }
            else
            {
                break;
            }
        }
    }
}
void display_Mem()
{
    int i;
    printf("\nMemory is : ");
    for(i=0;i<16;i++)
        printf("%d\t",Mem[i]);
}
void main()
{
    int ch,id,size,i;
    for(i=0;i<16;i++)
        Mem[i]=0;
    while(1)
    {
        printf("\nEnter choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: 
            {
                printf("\nEnter program id : ");
                scanf("%d",&id);
                printf("\nEnter the size in terms of pages : ");
                scanf("%d",&size);
                add_program(id,size);
                break;
            }
            case 2:
            {
                printf("\nEnter program id : ");
                scanf("%d",&id);
                rem_program(id);
                break;
            }
            case 3:
            {
                display_table();
                break;
            }
            case 4:
            {   
                display_Mem();
                break;
            }
            default:
            {
                exit(0);
                break;
            }
        }
    }
}
