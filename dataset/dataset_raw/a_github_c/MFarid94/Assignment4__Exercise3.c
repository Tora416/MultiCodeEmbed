

#include<stdio.h>
#define SIZE 10

void ReverseArray(int *ptr){ 
    int i;
    int temp;

    
    for(i=0 ; i<SIZE/2 ;i++){
        temp = *ptr;
        *ptr = *(ptr + (SIZE-1) - i*2);
        *(ptr + (SIZE-1) - i*2) = temp;
        ptr++;
    }
}

int main(void){
    setvbuf(stdout, NULL ,_IONBF , 0);
    setvbuf(stderr, NULL ,_IONBF , 0);
    int arr[SIZE];
    int i;
    int *ptr = arr;

    
    printf("Enter array elements: ");
    for(i=0 ; i<SIZE ;i++){
        scanf("%d",ptr);
        ptr++;
    }

    
    for(i=0 ; i<SIZE ;i++){
        printf("Array element before re-arranging: arr[%d] = %d\n",i,arr[i]);
    }

    
    ReverseArray(arr);

    ptr = arr;           
    
    for(i=0 ; i<SIZE ;i++){
        printf("Array element after re-arranging: arr[%d] = %d\n",i,*ptr);
        ptr++;
    }

    return 0;
}
