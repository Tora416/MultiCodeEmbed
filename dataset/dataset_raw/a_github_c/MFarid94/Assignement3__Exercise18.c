

#include<stdio.h>


int LongestConsecutive(int arr[],int size , int element){
    int max_consec = 0;
    int count = 0;
    int i;
    int ahead , current;
    
    for(i = 0; i < size ; i++){

        ahead = arr[i+1];
        current = arr[i];

        
        if(arr[i] == element){
            count++;

            
            if(count > max_consec){
                max_consec = count;
            }
        }

        
        if( ahead != current){
            count = 0;
        }
    }

    return max_consec;
}


int main(void){
    setvbuf(stdout , NULL , _IONBF , 0);
    setvbuf(stderr , NULL , _IONBF , 0);

    int size = 15;
    int arr[size];
    int maximum , element;
    int i;

    printf("Enter array elements: ");

    
    for(i=0 ; i<size ; i++){
        scanf("%d",&arr[i]);
    }

    printf("\n");
    printf("Enter required element: ");

    
    scanf("%d",&element);

    
    maximum = LongestConsecutive(arr , size , element);

    
    printf("Longest consecutive number of element %d is %d",element ,maximum);

    return 0;
}
