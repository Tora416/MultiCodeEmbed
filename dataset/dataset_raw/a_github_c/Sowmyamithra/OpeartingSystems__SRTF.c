
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct process
{
    char name[10];  
    int AT,BT,CT,TAT,WT,BT1,status;
};
void main()
{
    int n,i,j,temp,min,k,k1,init_temp,sum=0;
    float Waiting_time;
    char s[10];
    printf("\nEnter the number of processess : ");
    scanf("%d",&n);
    struct process p[n];
    for(i=0;i<n;i++)
    {
        printf("\nEnter name : ");
        scanf("%s",p[i].name);
        printf("\nEnter AT : ");
        scanf("%d",&p[i].AT);
        printf("\nEnter BT : ");
        scanf("%d",&p[i].BT);
        p[i].CT=0;
        p[i].status=0;
        p[i].BT1=p[i].BT;
    }
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(p[i].AT>p[j].AT)
            {
                temp=p[i].AT;
                p[i].AT=p[j].AT;
                p[j].AT=temp;
                temp=p[i].BT;
                p[i].BT=p[j].BT;
                p[j].BT=temp;
                temp=p[i].BT1;
                p[i].BT1=p[j].BT1;
                p[j].BT1=temp;
                strcpy(s,p[i].name);
                strcpy(p[i].name,p[j].name);
                strcpy(p[j].name,s);
            }
        }
    }
    k=0;
    temp=0;
    while(k<n)
    {
        init_temp=temp;
        min=1000;
        printf("\nq");
        for(i=0;i<n;i++)
        {
            printf("\nw");
            if(p[i].BT1<min && p[i].BT1!=0 && p[i].AT<=temp)
            {
                min=p[i].BT1;
            }
        }
        for(i=0;i<n;i++)
        {
            printf("\ne");
            if(p[i].AT<=temp && p[i].status==0 && p[i].BT1<=min)
            {
                p[i].BT1--;
                temp++;
                p[i].CT=temp;
                break;
            }
        }
        for(i=0;i<n;i++)
        {
            printf("\nr");
            if(p[i].BT1==0 && p[i].status==0)
            {
                k=k+1;
                p[i].status=k;
            }
        }
        if(init_temp==temp)
            temp++;
    }
    printf("\nstatus : ");
    for(i=0;i<n;i++)
        printf("\t%d",p[i].status);
    printf("\nprocess\tAT\tBT\tCT\tTAT\tWT");
    k1=1;
    while(k1<=k)
    {
        for(i=0;i<n;i++)
        {
            if(p[i].status==k1)
            {
                p[i].TAT=p[i].CT-p[i].AT;
                p[i].WT=p[i].TAT-p[i].BT;
                sum=sum+p[i].WT;
                printf("\n%s\t%d\t%d\t%d\t%d\t%d",p[i].name,p[i].AT,p[i].BT,p[i].CT,p[i].TAT,p[i].WT);
                k1++;
            }
        }
    }
    Waiting_time=(sum*1.0)/n;
    printf("\nAverage Waiting_time : %f",Waiting_time);
}