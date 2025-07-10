#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>

#define SIZE 10

void *sumofnum(void *arra);
void *productofnum(void *arra);

int n,i;
int main()
{
    int array[SIZE];
    printf("enter the array elements\n");
    while(array[i]!=999)
    {
    for(i=0;i<SIZE;i++)
    {
        scanf("%d",&array[i]);
        n=i;
        if(array[i]==999)
        break;

    }
    }
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL,sumofnum,&array);
    pthread_create(&thread2, NULL,productofnum,&array);

    
   pthread_join(thread1,NULL);
 
   
    pthread_join (thread2,NULL);
    
    return 0;
    
    
}


void *sumofnum(void *arra)
{
    int sum=0;
    int *arr=(int *)arra;
    for(i=0;i<n;i++)
    {
        sum+=arr[i];
    }
    printf("the sum is %d\n",sum);
    
}


void *productofnum(void *arra)
{
    float product=1;
    int *arr=(int *)arra;
    for(i=0;i<n;i++)
    {
        product=arr[i]*product;
        printf("%f\t",product);
    }
    printf("the product is %f\n",product);
}




