#include<stdio.h>
int po(int, int);
int main(){
    int n1,n2;
    printf("Enter the number 1 :\n");
    scanf("%d",&n1);
    printf("Enter the number 2 :\n");
    scanf("%d",&n2);
    po(n1,n2);
}

int po(int n1, int n2){
    int i,sum=0;
    
    if(n1>n2){  
        for(i=n2;i<=n1;i++){
            
            sum = sum + i*i;
    }
        printf("sum = %d",sum);
        
    }
    else{
        for(i=n1;i<=n2;i++){
            
            sum= sum + i*i;         
        }
        printf("sum = %d",sum);
    }
}