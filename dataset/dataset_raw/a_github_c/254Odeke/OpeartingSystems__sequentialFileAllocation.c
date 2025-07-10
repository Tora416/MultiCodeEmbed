#include<stdio.h>
#include<stdlib.h>
struct filestructure{
    char name[20];
    int starting_block;
    int no_of_blocks;
}file[20];
int i,j,disk[512];
int n;

void main(){
    for(i=0;i<512;i++)
        disk[i]=0;
        int x,y,flag=0;
    printf("Enter no.of files:");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        printf("Enter File Name:");
        scanf("%s",file[i].name);
        printf("Enter Starting Index:");
        scanf("%d",&file[i].starting_block);
        printf("Enter Size of Block:");
        scanf("%d",&file[i].no_of_blocks);
        x=file[i].starting_block;
        y=file[i].no_of_blocks;
        for(j=x;j<x+y;j++){
            if(disk[j]==1){
                printf("Sequencial Allocation is not possible\n");
                flag=1;
                break;
            }
        }
        if(flag==0){
            for(j=x;j<x+y;j++){
                disk[j]=1;
            }
            printf("Allocation is done sequentially\n");
        }
    }
}
