#include<stdio.h>
void main(){
    int  r_string[100],n,f,pf=0,count=0,m[10],i, j, k,;
    printf("Enter the length of reference string:");
    scanf("%d",&n);
    printf("Enter the reference string:");
    for(i=0;i<n;i++)
        scanf("%d",&r_string[i]);
    printf("Enter no. of frames:");
    scanf("%d",&f);
    for(i=0;i<f;i++)
        m[i]=-1;
    printf("The Page Replacement Process is:\n");
    for(i=0;i<n;i++){
        for(k=0;k<f;k++){
            if(m[k]==r_string[i])
                break;
        }
        if(k==f){
            m[count++]=r_string[i];
            pf++;
        }
        for(j=0;j<f;j++)
            printf("\t%d",m[j]);
        if(k==f)
            printf("\tPF No. %d\n",pf);
        if(count==f)
            count=0;
    }
    printf("\n The number of Page Faults using FIFO are %d",pf);
}
