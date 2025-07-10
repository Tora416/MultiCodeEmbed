#include <stdio.h>
#include <stdlib.h>
void inputArray(int arr[], int len){   
    for (int i = 0; i < len; i++)
        scanf("%d", &arr[i]);
}
void printArray(int arr[], int len){   
    for (int i = 0; i < len; i++)
            printf("%d ", arr[i]);
    printf("\n");
}
void selectionSort(int arr[], int len){ 
    int min,i,j,t;
    for(i=0;i<len-1;i++)
    {
        min=i;   
        for(j=i+1;j<len;j++)   
        {
            if(arr[j]<arr[min])
                min=j;;
        }
        t=arr[i];
        arr[i]=arr[min];   
        arr[min]=t;
        printf("Pass %d: ",i+1); 
        printArray(arr,len);   
    }
}
int main(){
    int len;
    scanf("%d", &len);   
    int arr[len];
    if (len<=0){   
            printf("ERROR: Empty list\n");
            exit(1);
    }
    inputArray( arr, len );   
    selectionSort(arr, len);   
    printf("Sorted: ");
        printArray(arr,len);   
    return 0;
}
