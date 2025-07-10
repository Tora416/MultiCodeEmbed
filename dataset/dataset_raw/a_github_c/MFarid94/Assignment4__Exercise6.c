

#include<stdio.h>
#define SIZE 10

int maximum;

int main(void){
    setvbuf(stdout , NULL , _IONBF , 0);
    setvbuf(stderr , NULL , _IONBF , 0);

    int i;
    int array[SIZE];
    int *ptr[SIZE];

    
    printf("Enter array elements: ");
    for(i=0 ; i<SIZE ; i++){
        scanf("%d",&array[i]);

        
        ptr[i] = &array[i];
    }

    
    maximum = *ptr[0];

    for(i=1 ; i<SIZE ; i++){

        if(maximum < *ptr[i]){
            maximum = *ptr[i];
        }
    }

    
    for(i=0 ; i<SIZE ;i++){
        printf("Array[%d] = %d\n",i,*ptr[i]);
    }

    printf("Maximum number is %d",maximum);

    return 0;
}

