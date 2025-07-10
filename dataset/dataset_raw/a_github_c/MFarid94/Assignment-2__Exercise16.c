

#include<stdio.h>



int countOnes(unsigned char number){
    unsigned char mask = 0x80;                          
    int ones = 0;
    
    for(int i = 0; i<8 ; i++){

        if((number<<i) & mask){
            ++ones;
        }
    }
    return ones;
}

int main(void){
    setvbuf(stdout , NULL , _IONBF , 0);                            
    setvbuf(stderr , NULL , _IONBF , 0);
    unsigned int number;
    int ones_count;
    printf("Enter an 8-bit number: ");
    scanf("%d",&number);                                            
    ones_count = countOnes(number);                                 
    printf("Number of 1's in given number is %d",ones_count);
    return 0;
}
