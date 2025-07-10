



#include <stdio.h> 

int main() 
{ 
    int array[2]; 
 
    
    
    printf("element 0: %d\n",array[0]); 
    printf("element 1: %d\n",array[1]);
    printf("%p\n",&array[0]);
    printf("%p\n",&array[1]);

    printf("element 2: %d\n", array[2]);
    printf("%p\n",&array[2]);
    printf("element 3: %d\n", array[3]);
    printf("%p\n",&array[3]);
    printf("element -1: %d\n", array[-1]);
    printf("%p\n",&array[-1]);
    
    
    
        
    return 0; 

}
