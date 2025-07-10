
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct process
{
    char name[10];
    int AT,BT,CT,TAT,WT;
};
void main()
{
    int n,i,j,temp,sum=0;
    float Waiting_time;
    char s[10];
    printf("\nEnter the number of processess : ");
    scanf("%d",&n);
    struct process p[n];
    for(i=0;i<n;i++)
    {
        printf("\nEnter process : ");
        scanf("%s",p[i].name);
        printf("\nEnter AT : ");    
        scanf("%d",&p[i].AT);
        printf("\nEnter BT : ");
        scanf("%d",&p[i].BT);
        p[i].CT=0;
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
                strcpy(s,p[i].name);
                strcpy(p[i].name,p[j].name);
                strcpy(p[j].name,s);
            }   
        }
    }
    p[0].CT=p[0].AT;
    for(i=0;i<n;i++)
    {
        if(i!=0)
            p[i].CT=p[i-1].CT;
        p[i].CT=p[i].CT+p[i].BT;
        p[i].TAT=p[i].CT-p[i].AT;
        p[i].WT=p[i].TAT-p[i].BT;
        sum=sum+p[i].WT;
    }
    printf("\nprocess\tAT\tBT\tCT\tTAT\tWT");
    for(i=0;i<n;i++)
        printf("\n%s\t%d\t%d\t%d\t%d\t%d",p[i].name,p[i].AT,p[i].BT,p[i].CT,p[i].TAT,p[i].WT);
    Waiting_time=(sum*1.0)/n;
    printf("\nAverage Waiting_time : %f",Waiting_time);
}
