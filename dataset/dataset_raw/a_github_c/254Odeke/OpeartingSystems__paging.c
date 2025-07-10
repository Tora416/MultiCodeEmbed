#include<stdio.h>
#include<math.h>
void main(){
    int memory_size,page_size;
    printf("Enter Memory Size:");
    scanf("%d",&memory_size);
    printf("Enter Page Size:");
    scanf("%d",&page_size);
    int n=memory_size/page_size;
    printf("No.of Pages available=%d\n",n);
    
    int m[n],i,j;
    for(i=0;i<n;i++){
        m[i]=0;
    }
    
    int p;
    printf("\nEnter No.of Processes:");
    scanf("%d",&p);
    int rem_pages=n;
    int req_pages,process_size;
    
    for(i=0;i<p;i++){
        printf("Enter Process %d size:",i+1);
        scanf("%d",&process_size);
        req_pages=(process_size/page_size);
        if(process_size%page_size!=0) req_pages++;
        if(req_pages>rem_pages){
            printf("Memory is lower than asked");
            continue;
        }
        int temp[req_pages];
        printf("Enter %d page numbers that are to be assigned to process %d:",req_pages,i+1);
        for(j=0;j<req_pages;j++){
            scanf("%d",&temp[j]);
        }
        for(j=0;j<req_pages;j++){
            if(m[temp[j]]!=0){
                printf("Page %d is already allocated",temp[j]);
                break;
            }
            m[temp[j]]=i+1;
            rem_pages--;
        }
    }
    
    printf("Main Memory:\n");
    printf("------------\n");
    for(i=0;i<n;i++){
        if(m[i]==0)
            printf("\tframe %d -- EMPTY\n",i);
        else    
            printf("\tframe %d -- process %d\n",i,m[i]);
    }
}
