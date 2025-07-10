

#include<stdio.h>

#define NO_ERROR_VALID_OPERATION 0
#define ERROR_INVALID_OPERATION 1


float calculate(float a , float b , char operator , int *error_ptr){
    float result;
    switch(operator){

            case '+':result = a+b;
                     *error_ptr = NO_ERROR_VALID_OPERATION;
                     break;

            case'-':result = a-b;
                    *error_ptr = NO_ERROR_VALID_OPERATION;
                    break;

            case'*':result = a*b;
                    *error_ptr = NO_ERROR_VALID_OPERATION;
                    break;

            case'/':result = a/b;
                    *error_ptr = NO_ERROR_VALID_OPERATION;
                    break;

            default:printf("ERROR INVALID INPUT OPERATION\n");
                    *error_ptr = ERROR_INVALID_OPERATION;
                    break;
    }
    return result;
}

int main(void){
        setvbuf(stdout , NULL , _IONBF , 0);                            
        setvbuf(stderr , NULL , _IONBF , 0);
        char op;
        float number1;
        float number2;
        float result;
        int error = NO_ERROR_VALID_OPERATION;       
        printf("Enter the required operation: ");
        scanf("%c",&op);                            
        printf("Enter first number: ");
        scanf("%f",&number1);                       
        printf("Enter second number: ");
        scanf("%f",&number2);                       
        result = calculate(number1 , number2 , op , &error);        
        if( error == NO_ERROR_VALID_OPERATION ){
            printf("Result = %f",result);
        }
        else if( error == ERROR_INVALID_OPERATION ){
            printf("No result , invalid operation");
        }
        return 0;
}
