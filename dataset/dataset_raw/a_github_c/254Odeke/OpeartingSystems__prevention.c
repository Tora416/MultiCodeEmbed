#include<stdio.h>

void main(){
    int pro,res,i,j;
    printf("Enter No.of Processes:");
    scanf("%d",&pro);
    printf("Enter No.of Resources:");
    scanf("%d",&res);
    
    int res_vector[res],res_allocated[res],res_avail[res];
    printf("Enter Resource Vector:");
    for(i=0;i<res;i++){
        scanf("%d",&res_vector[i]);
        res_allocated[i]=0;
    }
    
    int max[pro][res],allocated[pro][res],needed[pro][res];
    printf("Enter the Max Requirement matrix:\n");
    for(i=0;i<pro;i++){
        for(j=0;j<res;j++){
            scanf("%d",&max[i][j]);
        }
    }
    printf("Enter the Allocated Resource matrix:\n");
    for(i=0;i<pro;i++){
        for(j=0;j<res;j++){
            scanf("%d",&allocated[i][j]);
        }
    }
    
    for(i=0;i<pro;i++){
        for(j=0;j<res;j++){
            needed[i][j]=max[i][j]-allocated[i][j];
        }
    }
    
    for(i=0;i<res;i++){
        for(j=0;j<pro;j++){
            res_allocated[i]+=allocated[j][i];
        }
        res_avail[i]=res_vector[i]-res_allocated[i];
    }
    
    int completed[pro];
    for(i=0;i<pro;i++){
        completed[i]=0;
    }
    int flag,count=0;
    x:
    for(i=0;i<pro;i++){
        flag=0;
        for(j=0;j<res;j++){
            if(res_avail[j]<needed[i][j]||completed[i]==1){
                flag=1;
                count++;
                break;
            }
        }
        if(flag==0){
            printf("P%d ",i);
            for(j=0;j<res;j++){
                res_avail[j]+=allocated[i][j];
                allocated[i][j]=0;
                needed[i][j]=0;
            }
            completed[i]=1;
            goto x;
        }
    }
    if(count==pro){
        printf("No Safe Sequence is Possible");
    }
}
