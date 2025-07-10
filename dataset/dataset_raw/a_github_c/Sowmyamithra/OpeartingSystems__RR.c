
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char Queue[100];
int r=-1,f=-1;
struct process
{
    char name[10];  
    int AT,BT,CT,TAT,WT,BT1,status;
};
void enqueue(char c)
{
    if(f==-1 && r==-1)
    {
        f=f+1;
        r=r+1;
        Queue[r]=c;
    }
    else
    {
        r=r+1;
        Queue[r]=c;
    }
}
char dequeue()
{
    char c;
    if(r!=-1 && f!=-1)
    {
        c=Queue[f];
        f=f+1;
        return(c);
    }
}
int isempty()
{
    if(r==-1)
        return(1);
    else
        return(0);
}
void main()
{
    int n,i,j,temp,min,k,k1,init_temp,sum=0,T,flag=0,set=0;
    float Waiting_time;
    char s[10];
    printf("\nEnter time slice : ");
    scanf("%d",&T);
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
    while(isempty())
    {
        for(i=0;i<n;i++)
        {
            if(p[i].AT<=temp)
            {
                enqueue(p[i].name[0]);
                break;
            }
        }
        if(isempty())
            temp++;
    }
    while(k<n)
    {
        s[0]=dequeue();
        for(i=0;i<n;i++)
        {
            flag=0;
            if(p[i].name[0]==s[0] && p[i].BT1!=0)
            {
                printf("%c\t",s[0]);
                flag=1;
                set=i;
                if(p[i].BT1>T)
                {
                    p[i].BT1=p[i].BT1-T;
                    temp=temp+T;
                    p[i].CT=temp;
                }
                else
                {
                    temp=temp+p[i].BT1;
                    p[i].CT=temp;
                    p[i].BT1=0;
                }
            }
            if(flag==1)
            {
                for(j=0;j<n;j++)
                {
                    if(p[j].name[0]!=s[0] && p[j].AT<=temp && p[j].BT1!=0)
                        enqueue(p[j].name[0]);
                }
                if(p[set].BT1!=0)
                    enqueue(p[set].name[0]);
                break;
            }
        }
        for(i=0;i<n;i++)
        {
            if(p[i].BT1==0 && p[i].status==0)
            {
                k++;
                p[i].status=k;
            }
        }   
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