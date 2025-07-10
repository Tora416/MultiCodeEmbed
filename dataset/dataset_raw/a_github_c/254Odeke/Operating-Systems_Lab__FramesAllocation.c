#include<stdio.h>
#include<stdlib.h>

void main(){
    int n,option,frames;
    int size[10];
    int i,a[10],total=0;
    char p[10];
    printf("No.of Processes present:");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        printf("Enter the process name-");
        scanf("%s",&p[i]);
        printf("Enter the size of process-");
        scanf("%d",&size[i]);
    }
    printf("No.of Frames present:");
    scanf("%d",&frames);
    while(1){
        printf("\n1.Fixed Allocation\t2.Proportional Allocation\t3.Exit:-");
        scanf("%d",&option);
        switch(option){
            case 1: for(i=0;i<n;i++){
                        printf("\nAllocation of frames to process %c is %d",p[i],frames/n);
                    }
                    break;
                    
            case 2: for(i=0;i<n;i++) total = total+size[i]; 
                    for(i=0;i<n;i++){
                        printf("\nAllocation of frames for process %c is %d",p[i],(size[i]*frames)/total);
                    }
                    break;
            case 3: exit(0);        
            default: printf("\nInvalid Selection");
        }
    }
}
