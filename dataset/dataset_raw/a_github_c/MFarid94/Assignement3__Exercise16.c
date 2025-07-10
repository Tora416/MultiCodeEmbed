

#include<stdio.h>


void ReverseArray(int arr[] ,int size){
    int i, temp;

    
    for(i=0 ; i<size/2 ; i++){
        temp = arr[i];
        arr[i] = arr[size-1 - i];
        arr[size-1 -i] = temp;
    }
}

int main(void){
    setvbuf(stdout , NULL , _IONBF , 0);
    setvbuf(stderr , NULL , _IONBF , 0);

    int k , j;
    int size = 5;
    int arr[5];

    printf("Enter elements of array: ");

    
    for(k=0 ; k<size ; k++){
        scanf("%d",&arr[k]);
    }

    
    ReverseArray(arr,size);

    printf("Array after being reversed: ");
    
    for(j=0 ; j<size ; j++){
        printf("%d ",arr[j]);
    }

    return 0;
}
