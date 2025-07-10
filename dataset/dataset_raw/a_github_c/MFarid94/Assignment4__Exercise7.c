

#include<stdio.h>


void Swap(int *X, int *Y){
    *X = *X ^ *Y;
    *Y = *X ^ *Y;
    *X = *X ^ *Y;
}

int main(void){
    setvbuf(stdout , NULL , _IONBF , 0);
    setvbuf(stderr , NULL , _IONBF , 0);

    int num1 , num2 ;
    void (*ptr)(int *,int *) = Swap;

    
    printf("Enter first number: ");
    scanf("%d",&num1);

    printf("Enter second number: ");
    scanf("%d",&num2);

    
    printf("Displaying two number before swapping\n");
    printf("First number is %d , Second number is %d\n",num1,num2);

    
    (*ptr)(&num1 , &num2);

    
    printf("Displaying two numbers after swapping\n");
    printf("First number is %d , Second number is %d",num1,num2);

    return 0;
}
