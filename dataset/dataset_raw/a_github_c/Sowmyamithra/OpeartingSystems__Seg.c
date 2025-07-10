
#include<stdio.h>
#include<stdlib.h>
int Mem[16];
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
void rem_program(int id)
{
    int i,j,k;
    for(i=0;i<16;i++)
    {
        if(Mem[i]==id)
            break;
    }
    for(k=15;k>=0;k--)
    {
        if(Mem[k]==id)
            break;
    }
    j=k-i+1;
    k=k+1;
    while(k<16)
    {
        Mem[i]=Mem[k];
        i++;
        k++;
    }
    k=15;
    while(j!=0)
    {
        Mem[k]=0;
        k--;
        j--;
    }
}
void add_program(int id,int size)
{
    int ct=get_count(),i,ch=1,id1;
    if(ct>=size)
    {
        for(i=0;i<16 && size>0;i++)
        {
            if(Mem[i]==0)
            {
                Mem[i]=id;
                size--;
            }
        }
    }
    else
    {
        while(ch==1)
        {
            printf("\nIs there any possibility of removing a program : ");
            scanf("%d",&ch);
            if(ch==1)
            {
                printf("\nEnter id : ");
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
            for(i=0;i<16 && size>0;i++)
            {
                if(Mem[i]==0)
                {
                    Mem[i]=id;
                    size--;
                }
            }
        }
        else
        {
            printf("\nNot possible");
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
    int ch,id,size,temp;
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
                printf("\nEnter program size in terms of no of segments : ");
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