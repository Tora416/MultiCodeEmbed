
#include<stdio.h>
#include<stdlib.h>
int Mem,block;
struct program
{
    char name[10];
    int If,size,status;
};
void main()
{
    int n,i,size,IF=0,EF=0;
    printf("\nEnter the size of memory : ");
    scanf("%d",&Mem);
    printf("\nEnter size of each block : ");
    scanf("%d",&block);
    printf("\nEnter the number of programs : ");
    scanf("%d",&n);
    struct program p[n];
    for(i=0;i<n;i++)
    {
        printf("\nEnter name : ");
        scanf("%s",p[i].name);
        printf("\nEnter size : ");
        scanf("%d",&p[i].size);
        p[i].If=0;
        p[i].status=0;
    }
    for(i=0;i<n;i++)
    {
        if(p[i].size<=block)
        {
            p[i].status=1;
            p[i].If=block-p[i].size;
            IF=IF+p[i].If;
        }
        else
        {
            EF=EF+block;
        }
    }
    printf("\nprogram\tsize\tIF\n");
    for(i=0;i<n;i++)
        printf("%s\t%d\t%d\n",p[i].name,p[i].size,p[i].If);
    printf("\nTotal Internal Fragmentation is : %d",IF);
    printf("\nTotal External Fragmentation is : %d",EF);
}