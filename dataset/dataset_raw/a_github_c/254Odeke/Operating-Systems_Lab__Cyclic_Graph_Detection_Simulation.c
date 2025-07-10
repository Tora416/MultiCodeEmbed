#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
int matrix[10][10],visited[10],n,i,j;
bool isCyclic(int);
void main(){
    printf("Enter the No.of Processes present in wait for graph:");
    scanf("%d",&n);
    printf("Enter the adjacency matrix:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&matrix[i][j]);
        }
    }
    for(i=0;i<n;i++){
        visited[i]=0;
    }
    
    bool flag=false;
    for(i=0;i<n;i++){
        visited[i]=1;
        for(j=0;j<n;j++){
            if(matrix[i][j]==0) continue;
            flag = isCyclic(j);
            if(flag==true){
                printf("Cycle is present");
                exit(0);
            }
        }
        visited[i]=0;
    }
    if(flag==false){
        printf("Cycle is not present");
    }
}
bool isCyclic(int cur){
    if(visited[cur]==1){
        return true;
    }
    visited[cur]=1;
    bool flag=false;
    for(i=0;i<n;i++){
        if(matrix[cur][i]==0) continue;
        flag=isCyclic(i);
        if(flag==true)
            return true;
    }
    visited[cur]=0;
    return false;
}
