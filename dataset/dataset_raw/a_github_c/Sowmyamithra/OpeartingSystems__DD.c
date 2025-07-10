
#include<stdio.h>
#include<stdlib.h>
#define m 3
#define n 4
int available[m],allocation[n][m],request[n][m];
int safety_module()
{
    int work[m],finish[n],i,j,flag=0,set;
    for(i=0;i<m;i++)
        work[i]=available[i];
    for(i=0;i<n;i++)
    {
        flag=0;
        for(j=0;j<m;j++)
        {
            if(allocation[i][j]!=0)
            {
                flag=1;
                break;
            }
            else
                continue;
        }
        if(flag==1)
            finish[i]=0;
        else
            finish[i]=1;
    }
    while(1)
    {
        set=-1;
        for(i=0;i<n;i++)
        {
            flag=0;
            for(j=0;j<m;j++)
            {
                if(request[i][j]<=work[j])
                    continue;
                else
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0 && finish[i]==0)
            {
                set=i;
                finish[i]=1;
                for(j=0;j<m;j++)
                    work[j]=work[j]+allocation[i][j];
                break;
            }
        }
        if(set==-1)
            break;
        else
            continue;
    }
    flag=0;
    printf("\nProcessess in deadlock are : \n");
    for(i=0;i<n;i++)
    {
        if(finish[i]!=1)
        {
            printf("%d\t",i);
            flag=-1;
        }
    }
    if(flag==0)
        return(1);
    else
        return(0);
}
void main()
{
    int i,j,s;
    printf("\nEnter the available resources  : ");
    for(i=0;i<m;i++)
        scanf("%d",&available[i]);
    printf("\nEnter allocation : ");    
    for(i=0;i<n;i++)
    {
        printf("\nfor process %d : ",i);
        for(j=0;j<m;j++)
        {
            scanf("%d",&allocation[i][j]);
        }
    }
    printf("\nEnter request : \n");
    for(i=0;i<n;i++)
    {
        printf("\nfor process %d : ",i);
        for(j=0;j<m;j++)
        {
            scanf("%d",&request[i][j]);
        }
    }
    s=safety_module();
    if(s==1)
        printf("No Deadlock");
    else
        printf("\nDeadlock");
}