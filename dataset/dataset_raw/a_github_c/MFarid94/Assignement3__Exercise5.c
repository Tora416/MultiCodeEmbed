

#include<stdio.h>


int LinearSearch(int arr[] , int element , int size ){
    int i;

    
    for(i =0; i <size ; i++){
        if(arr[i] == element)
            return i;           
    }
    return -1;  
}

int main(void){
    setvbuf(stdout , NULL , _IONBF , 0);
    setvbuf(stderr , NULL , _IONBF , 0);
    int i ;
    int size = 5;
    int arr[size];
    int result, element;
    printf("Enter array of numbers:");

    
    for(i=0 ; i<size ; i++){
        scanf("%d",&arr[i]);
    }

    printf("Enter required element:");

    
    scanf("%d",&element);

    
    result = LinearSearch(arr, element ,size);

    if(result == -1){
        printf("Item is not on the list");
    }
    else{
        printf("The index of required item is %d",result);
    }
    return 0;
}

