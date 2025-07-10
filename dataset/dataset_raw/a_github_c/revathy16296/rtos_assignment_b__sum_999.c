#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<fcntl.h>

#define SI 10

int i, array[SI],n=0;
float sum_of_num();
float product_of_num();



int main()
{
    int fd1[2],fd2[2];
    pipe(fd1);
    pipe(fd2);
    
    printf("enter the array elements\n");
    while(array[i]!=999)
    {
    for(i=0;i<SI;i++)
    {
        scanf("%d",&array[i]);
        n=i;
        if(array[i]==999)
        break;

    }
    }
    pid_t pid;
    pid=fork();
    if(pid==0)
    {
        printf("inside child-----\n");
        close(fd1[0]);
        close(fd2[0]);
        float product,sum;
        sum=sum_of_num();
        printf("the sum is %f\n",sum);
        write(fd1[1],&sum,sizeof(sum));
        product=product_of_num();
        printf("the product is %f\n",product);
        write(fd2[1],&product,sizeof(product));

        close(fd1[1]);
        close(fd2[1]);      
        
    }
    else
    {
        wait(NULL);
        printf("-----inside parent process------\n");
        close(fd1[1]);
        close(fd2[1]);
        float avg=0,sum,product;
        read(fd1[0],&sum,sizeof(sum));
        read(fd2[0],&product,sizeof(product));

        printf("\tthe sum is %f\n",sum);
        avg=sum/SI;
        printf("\tthe average is %f\n",avg);
        printf("\tthe product is %f\n",product);

        close(fd1[0]);
        close(fd2[0]);
    }
        
        return 0;
}

        
    float product_of_num()
{
    float product=1;
    for(i=0;i<n;i++)
    {
        product*=array[i];
    }
    return product;
}


float sum_of_num()
{
    float sum=0;
    for(i=0;i<n;i++)
    {
        sum+=array[i];
    }
    return sum;
}