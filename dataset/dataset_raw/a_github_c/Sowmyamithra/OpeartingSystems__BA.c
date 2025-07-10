
#include<stdio.h>
#include<stdlib.h>
#define m 3
#define n 5
int available[m],max[n][m],allocation[n][m],need[n][m],request[n][m];
int safety_module()
{
    int work[m],finish[n],i,j,flag=0;
    for(i=0;i<m;i++)
        work[i]=available[i];
    for(i=0;i<n;i++)
        finish[i]=0;
    while(1)
    {
        for(i=0;i<n;i++)
        {
            flag=0;
            for(j=0;j<m;j++)
            {
                if(need[i][j]<=work[j])
                    continue;
                else
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0 && finish[i]==0)
            {
                finish[i]=1;
                for(j=0;j<m;j++)
                    work[j]=work[j]+allocation[i][j];
                break;
            }
        }
        if(i==5)
            break;
        else
            continue;
    }
    for(i=0;i<n;i++)
    {
        if(finish[i]!=1)
            break;
    }
    if(i==5)
        return(1);
    else
        return(0);
}
void resource_request(int pr)
{
    int i,s,flag=-1;
    for(i=0;i<m;i++)
    {
        if(request[pr][i]<=need[pr][i])
            continue;
        else
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
        printf("Terminate!");
    else
    {
        for(i=0;i<m;i++)
        {
            if(request[pr][i]<=available[i])
                continue;
            else
            {
                flag=1;
                break;
            }
        }   
        if(flag==1)
            printf("Process has to wait");
        else
        {
            for(i=0;i<m;i++)
            {
                available[i]=available[i]-request[pr][i];
                allocation[pr][i]=allocation[pr][i]+request[pr][i];
                need[pr][i]=need[pr][i]-request[pr][i];
            }
            s=safety_module();
            if(s==1)
                printf("\nRequest Granted");
            else
            {
                printf("\nRestore");
                for(i=0;i<m;i++)
                {
                    available[i]=available[i]+request[pr][i];
                    allocation[pr][i]=allocation[pr][i]-request[pr][i];
                    need[pr][i]=need[pr][i]+request[pr][i];
                }
            }
        }
    }
}
void main()
{
    int i,j,pr;
    printf("\nEnter the available resources  : ");
    for(i=0;i<m;i++)
        scanf("%d",&available[i]);
    printf("\nEnter maximum : ");   
    for(i=0;i<n;i++)
    {
        printf("\nfor process %d : ",i);
        for(j=0;j<m;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }
    printf("\nEnter allocation : ");    
    for(i=0;i<n;i++)
    {
        printf("\nfor process %d : ",i);
        for(j=0;j<m;j++)
        {
            scanf("%d",&allocation[i][j]);
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            need[i][j]=max[i][j]-allocation[i][j];
        }
    }
    printf("\nenter the process to take request : ");
    scanf("%d",&pr);
    printf("\nEnter request : ");
    for(j=0;j<m;j++)
    {
        scanf("%d",&request[pr][j]);
    }
    resource_request(pr);
}