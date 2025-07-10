

#include<stdio.h>


void SelectionSorting(int arr[],const int size ){
    int i , j , min , temp;

    
    for(i = 0 ; i < (size-1) ; i++){
        
        min = i;

            for(j = i+1 ; j < size ; j++){

                if(arr[j]<arr[min]){
                    min = j;
                }
            }

            
            temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
    }
}

int main(void){
    setvbuf(stdout , NULL , _IONBF , 0);
    setvbuf(stderr , NULL , _IONBF , 0);
    int i ,j ,k;
    const int size = 5;
    int arr[size];

    printf("Enter array elements:\n");

    
    for(i=0 ; i<size ; i++){
        scanf("%d",&arr[i]);
    }

    printf("Array before sorting:\n");

    
    for(j=0 ; j<size ; j++){
        printf("%d\t",arr[j]);
    }

    
    SelectionSorting(arr,size);

    printf("\n");
    printf("Array after sorting:\n");

    
    for(k=0 ; k<size ; k++){
        printf("%d\t",arr[k]);
    }

    return 0;
}
