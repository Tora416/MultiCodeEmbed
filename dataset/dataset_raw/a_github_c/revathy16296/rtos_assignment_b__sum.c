#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>


#define SI 10


int array[SI],i;
float sum_of_num();
float product_of_num();

int main()
{
    int pid,fd[2];
    pipe(fd);
    printf("enter the 10 values to be calculated\n");
    for(i=0;i<SI;i++)
    {
        scanf("%d",&array[i]);
    }
    pid=fork();
    if (pid==0)
    {
        printf("inside child-----\n");
        close(fd[0]);
        float product,sum;
        sum=sum_of_num();
        printf("the sum is %f\n",sum);
        write(fd[1],&sum,sizeof(sum));
        product=product_of_num();
        printf("the product is %f\n",product);
close(fd[1]);       
    }
    else
    {
        wait(NULL);
        printf("-----inside parent process------\n");
        close(fd[1]);
        float avg=0,sum;
        read(fd[0],&sum,sizeof(sum));
        printf("\tthe sum is %f\n",sum);
        avg=sum/SI;
        printf("\tthe average is %f\n",avg);
    }
    return 0;
}
    
        
    float product_of_num()
{
    float product=1;
    for(i=0;i<SI;i++)
    {
        product*=array[i];
    }
    return product;
}


float sum_of_num()
{
    float sum=0;
    for(i=0;i<SI;i++)
    {
        sum+=array[i];
    }
    return sum;
}


    
        
        

