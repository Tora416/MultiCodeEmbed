

#include<stdio.h>
#define CHECK_LOWER_FALSE   0
#define CHECK_LOWER_TRUE    1

int test_case = CHECK_LOWER_TRUE;                               


char lower_to_upper(char alphabet){
    if( alphabet >= 'a' && alphabet <= 'z' ){
        alphabet = alphabet - 32;                                   
    }
    else{
        test_case = CHECK_LOWER_FALSE;
    }
    return alphabet;
}

int main(void){
    setvbuf(stdout , NULL , _IONBF , 0);                            
    setvbuf(stderr , NULL , _IONBF , 0);
    char alphabet;                                                  
    char uppercase;                                                 
    printf("Please enter a lowercase letter: ");
    scanf("%c",&alphabet);                                          
    uppercase = lower_to_upper(alphabet);                           
    if( test_case == CHECK_LOWER_TRUE ){
    printf("Uppercase letter %c of corresponding Lowercase letter %c ",uppercase,alphabet);
       }
    else {
        printf("Invalid input, please enter a lowercase letter ");
    }
    return 0;
}
