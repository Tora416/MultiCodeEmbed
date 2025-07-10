

#include<stdio.h>



void display_prime(int num1, int num2){
    int number = num1;
    int rem_of_two, rem_of_three;                           

    
    for (int i = num1; i<=num2 ; ){
        rem_of_two = number % 2;
        rem_of_three = number % 3;

        
        if(number == 2 || number == 3){
                printf("%d ",number);                                               
            }
            else{
                
                if( rem_of_two == 0 || rem_of_three == 0){
                    i++;
                    number++;
                    continue;
                }
                else{
                    printf("%d ",number);
                }
            }
        i++;
        number++;
    }
}

int main(void){
    setvbuf(stdout , NULL , _IONBF , 0);                            
    setvbuf(stderr , NULL , _IONBF , 0);
    int number1, number2;                                           
    printf("Enter first number: ");
    scanf("%d",&number1);                                           
    printf("Enter second number: ");
    scanf("%d",&number2);                                           
    display_prime(number1,number2);                                 
    return 0;
}
