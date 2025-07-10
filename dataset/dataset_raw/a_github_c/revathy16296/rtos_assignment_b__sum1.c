#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>

#define SIZE 10
void *sum_array(void *a[SIZE]);
void* product_of_elements(void* a[SIZE]);
pthread_mutex_t mutex;
int  array[SIZE];
    int i;
int main()
{
    
    printf("enter the array numbers\n");
    for(i=0;i<SIZE;i++)
    {
        scanf("%d",&(array[i]));
    }
    pthread_t thread1, thread2;
    printf("the thread is created\n");
    pthread_create(&thread1, NULL, sum_array, &array);
    pthread_create(&thread2, NULL, product_of_elements,&array );
    
    
    pthread_join(thread1,NULL);
    pthread_join (thread2,NULL);
    
    
    pthread_mutex_destroy(&mutex);
    
return 0;
}


void* sum_array(void *a[SIZE])
{
    pthread_mutex_lock(&mutex);
    float sum=0;
    int *ar=(int *)a;
    printf("inside the first thread\n");
    for(i=0;i<SIZE;i++)
    {
        sum += ar[i];
        printf("%f\t",sum);
    }
    printf("the sum is %f\n",sum);
    float average;
    average=sum/10;
    printf("the average is %f\n",average);
    pthread_mutex_unlock(&mutex);
}

void* product_of_elements(void* a[SIZE])
{
    float product=1;
    int* ar=(int*) a;
    for(i=0;i<SIZE;i++)
    {
         product =ar[i] * product;
    }
    printf("product=%f\n",product);
}