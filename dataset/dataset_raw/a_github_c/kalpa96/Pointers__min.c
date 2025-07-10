#include<stdio.h>

int main(){
    int num1,num2,num3;
    int *p1,*p2,*p3;

    printf("Enter Number 1 : ");
    scanf("%d",&num1);
    printf("Enter Number 2 : ");
    scanf("%d",&num2);
    printf("Enter Number 3 : ");
    scanf("%d",&num3);
    printf("\n");
    
    p1 = &num1;
    p2 = &num2;
    p3 = &num3;
    
    
    if(*p1 > *p2){
        if(*p1 > *p3){
            printf("Maximum is : %d\n",*p1);
        }

        else{
            printf("Maximum is : %d\n",*p3);
        }
    }
    else{
        if(*p2 > *p3){
            printf("Maximum is : %d\n",*p2);
        }
        else{
            printf("Maximum is : %d\n",*p3);
        }
    }
    
    
    if(*p1 < *p2){
        if(*p1 < *p3){
            printf("Minimum is : %d",*p1);
        }
        else{
            printf("Minimum is : %d",*p3);
        }
    }
    else{
        if(*p2 < *p3){
            printf("Minimum is : %d",*p2);
        }
        else{
            printf("Minimum is : %d",*p3);
        }
    }
    return 0;
}