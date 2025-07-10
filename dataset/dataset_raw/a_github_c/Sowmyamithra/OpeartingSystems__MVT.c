
#include<stdio.h>
#include<stdlib.h>
int Mem;
struct program
{
    char name[10];
    int size,status;
};
void main()
{
    int n,i,rem,EF=0;
    printf("\Enter the size of memory : ");
    scanf("%d",&Mem);
    printf("\nEnter the number of programs : ");
    scanf("%d",&n);
    struct program p[n];
    rem=Mem;
    for(i=0;i<n;i++)
    {
        printf("\nEnter name : ");
        scanf("%s",p[i].name);
        printf("\nEnter size : ");
        scanf("%d",&p[i].size);
        p[i].status=0;
    }
    for(i=0;i<n;i++)
    {
        if(p[i].size<=rem)
        {
            p[i].status=1;
            rem=rem-p[i].size;
        }
    }
    EF=rem;
    printf("\nprogram\tsize\tstatus\n");
    for(i=0;i<n;i++)
        printf("%s\t%d\t%d\n",p[i].name,p[i].size,p[i].status);
    printf("\nTotal External Fragmentation is : %d",EF);
}