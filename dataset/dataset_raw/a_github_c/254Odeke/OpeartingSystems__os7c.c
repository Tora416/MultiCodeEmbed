#include<stdio.h>
void main(){
    int rs[50], i, j, k, n, f, count[20], m[20], min, pf=0;
    printf("Enter number of page references:");
    scanf("%d",&n);
    printf("Enter the reference string:");
    for(i=0;i<n;i++)
        scanf("%d",&rs[i]);
    printf("Enter the available no. of frames:");
    scanf("%d",&f);
    for(i=0;i<f;i++){
        count[i]=0;
        m[i]=-1;
    }
    printf("\nThe Page Replacement Process is\n");
    for(i=0;i<n;i++){
        for(k=0;k<f;k++){
            if(rs[i]==m[k]){
                count[k]++;
                break;
            }
        }
        if(k==f){
            if(i<f){
                m[i]=rs[i];
                count[i]++;
            }
            else{
                min = 0;
                for(j=1;j<f;j++)
                    if(count[min]>count[j])
                        min=j;
                m[min]=rs[i];
                count[min]=1;
            }
            pf++;
        }
        for(j=0;j<f;j++)
            printf("%d\t",m[j]);
        if(k==f)
            printf("PF No. %d",pf);
        print("\n");    
    }
    printf("\n Total number of page faults: %d",pf);
}
