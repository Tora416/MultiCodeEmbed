

#include<stdio.h>
#define SIZE 20
#define FOR_WHILE 1
#define RECURSIVE 2


int ForFibonacci(int arr[],int index){
    int i;

    
    arr[0] = 1;
    arr[1] = 1;

    
    for( i=2 ; i<(SIZE-1) ; i++ ){
        arr[i] = arr[i-1] + arr[i-2];
    }

    
    return arr[index];
}


long RecursiveFibonacci(long index){

    if(index == 0 || index == 1){
        return 1;
    }
    else{
        return RecursiveFibonacci(index-2) + RecursiveFibonacci(index-1);
    }
}

int main(void){
    setvbuf(stdout , NULL , _IONBF , 0);
    setvbuf(stderr , NULL , _IONBF , 0);

    int arr[SIZE];
    int function_type;                                                                      
    int index;
    int result_forwhile;
    long result_fibo;

    
    printf("Enter required element in Fibonacci series: ");
    scanf("%d",&index);
    printf("\n");

    
    printf("Type 1 for ForWhile function or type 2 for Recursive function: ");
    scanf("%d",&function_type);

    if(function_type == FOR_WHILE){

        
        result_forwhile = ForFibonacci(arr,index);
        printf("The %d element in fibonacci series is %d",index,result_forwhile);
    }
    else if(function_type == RECURSIVE){

        
        result_fibo = RecursiveFibonacci(index);
        printf("The %d element in recursive fibonacci is %ld",index , result_fibo);
    }


    return 0;
}
