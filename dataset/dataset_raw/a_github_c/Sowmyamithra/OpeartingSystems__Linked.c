
#include<stdio.h>
#include<stdlib.h>
struct Disk
{
    int id,next_index;
}disk[16];
int ispossible()
{
    int i,ct=0;
    for(i=0;i<16;i++)
    {
        if(disk[i].id==0)
            ct++;
    }
    return(ct);
}
void add_file(int id,int size)
{
    int ct=ispossible(),i,j;
    if(ct>=size)
    {
        for(i=0;i<16 && size>0;i++)
        {
            if(disk[i].id==0)
            {
                disk[i].id=id;
                size--;
                for(j=i+1;j<16;j++)
                {
                    if(disk[j].id==0 && size>0)
                    {
                        disk[i].next_index=j;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        printf("\nNot possible");
    }
}
void rem_file(int id)
{
    int i;
    for(i=0;i<16;i++)
    {
        if(disk[i].id==id)
        {
            disk[i].id=0;
            disk[i].next_index=-1;
        }
    }
}
void display()
{
    int i;
    printf("\nDisk is : "); 
    for(i=0;i<16;i++)
    {
        printf("\n%d\t%d",disk[i].id,disk[i].next_index);
    }
}
void main()
{
    int ch,id,size,i;
    for(i=0;i<16;i++)
    {
        disk[i].id=0;
        disk[i].next_index=-1;
    }
    while(1)
    {
        printf("\nEnter choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: 
            {
                printf("\nEnter file id : ");
                scanf("%d",&id);
                printf("\nEnter size : ");
                scanf("%d",&size);
                add_file(id,size);
                break;
            }
            case 2:
            {
                printf("\nEnter file id : ");
                scanf("%d",&id);
                rem_file(id);
                break;
            }
            case 3:
            {
                display();
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