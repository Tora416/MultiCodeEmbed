

#include<stdio.h>


void BubbleSort(int arr[], const int array_size){
        int i, j;
        int temp;
        for(i=1 ; i<= array_size ; i++){
            for(j=0 ; j<= (array_size - 1) ; j++){

                if(arr[j]>arr[j+1]){
                    temp = arr[j+1];
                    arr[j+1] = arr[j];
                    arr[j] = temp;
                }
            }
        }
}

int main(void){

    const int array_size =5;
    int arr[array_size];
    int i, j, k;


    for(i=0 ; i<array_size ; i++){
            scanf("%d",&arr[i]);
        }

    printf("Array before sorting: \n");
    for(j=0 ; j<array_size ; j++){
            printf("%d\t",arr[j]);
        }

    BubbleSort(arr, array_size);

    printf("\n");
    printf("Array after sorting: \n");
    for(k=0 ; k<array_size ; k++){
        printf("%d\t",arr[k]);
    }

    return 0;
    }

