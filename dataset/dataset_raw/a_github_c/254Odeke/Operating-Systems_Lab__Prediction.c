#include<stdio.h>

void main(){
    int res,pro,i,j,n;
    printf("Enter No.of Processes:");
    scanf("%d",&pro);
    printf("Enter No.of Resources:");
    scanf("%d",&res);
    int res_vector[res],res_avail[res],res_allocated[res];
    printf("Enter Resource vector:");
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
    
    while(pro!=0){
        printf("Enter process number that is to be executed:");
        scanf("%d",&n);
        for(i=0;i<res;i++){
            if(needed[n][i]>res_avail[i]){
                printf("Resources cannot be allocated to this process now:\n");
                printf("\nIt is unsafe state");
                exit(0);
            }
        }
        if(i==res){
            printf("Resources are allocated to the process %d and executed\n",n);
            for(j=0;j<res;j++){
                res_avail[j]+=allocated[n][j];
            }
        }
    pro--;
    }
    if(pro==0)
        printf("\nIt is safe state");
}