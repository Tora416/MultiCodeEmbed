
#include<stdio.h>
#include<stdlib.h>
int disk[16],d_array[16][16],pos=0;
int ispossible()
{
    int i,ct=0;
    for(i=1;i<16;i++)
    {
        if(disk[i]==0)
            ct++;
    }
    return(ct);
}
void add_file(int id,int size)
{
    int ct=ispossible(),i,j;
    if(ct>=size)
    {
        d_array[pos][0]=id;
        j=1;
        for(i=1;i<16 && size>0;i++)
        {
            if(disk[i]==0)
            {
                disk[i]=id;
                size--;
                d_array[pos][j]=i;
                j++;
            }
        }
        pos++;
    }
    else
    {
        printf("\nNot possible");
    }
}
void rem_file(int id)
{
    int i,j;
    for(i=1;i<16;i++)
    {
        if(disk[i]==id)
        {
            disk[i]=0;
        }
    }
    for(i=0;i<16;i++)
    {
        if(d_array[i][0]==id)
        {
            d_array[i][0]=0;
            for(j=1;j<16;j++)
            {
                if(d_array[i][j]!=0)
                    d_array[i][j]=0;
                else
                    break;
            }
        }
    }
}
void display()
{
    int i,j;
    printf("\nDisk is : "); 
    for(i=1;i<16;i++)
    {
        printf("\t%d",disk[i]);
    }
    printf("\nd_array is : ");
    for(i=0;i<pos;i++)
    {
        if(d_array[i][0]!=0)
        {
            printf("\n%d",d_array[i][0]);
            for(j=1;j<16;j++)   
            {
                if(d_array[i][j]!=0)
                    printf("\t%d",d_array[i][j]);
                else
                    break;
            }
        }
    }
}
void main()
{
    int ch,id,size,i;
    for(i=0;i<16;i++)
    {
        disk[i]=0;
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