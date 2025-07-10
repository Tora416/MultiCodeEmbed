
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct process
{
    char name[10];
    int AT,BT,CT,TAT,WT,Pr,status;
};
void main()
{
    int n,i,j,sum=0,temp,init_temp,k=0,k1;
    char s[10];
    float Waiting_time;
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
        printf("\nEnter priority : ");
        scanf("%d",&p[i].Pr);
        p[i].status=0;
    }
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(p[i].Pr>p[j].Pr)
            {
                temp=p[i].AT;
                p[i].AT=p[j].AT;
                p[j].AT=temp;
                temp=p[i].BT;
                p[i].BT=p[j].BT;
                p[j].BT=temp;
                temp=p[i].Pr;
                p[i].Pr=p[j].Pr;
                p[j].Pr=temp;
                strcpy(s,p[i].name);
                strcpy(p[i].name,p[j].name);
                strcpy(p[j].name,s);
            }   
        }
    }
    temp=0;
    while(k<n)
    {
        init_temp;
        for(i=0;i<n;i++)
        {
            if(p[i].AT<=temp && p[i].status==0)
            {
                p[i].CT=p[i].BT+temp;
                temp=temp+p[i].BT;
                k++;
                p[i].status=k;
                break;
            }
        }
        if(init_temp==temp)
            temp++;
    }
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