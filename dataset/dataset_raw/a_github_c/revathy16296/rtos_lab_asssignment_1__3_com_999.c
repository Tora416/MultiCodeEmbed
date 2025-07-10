#include<stdio.h>
#include<stdlib.h>
#define SI 10

int sum_of_num(int array[],int n);
float average_of_num(int sum,int n);
float product_of_num(int array[],int n);

int i;



int main(int argc,char *argv[])
{
    int array[SI],n=0,sum;
    float product,average;


    while(atoi(argv[i])!=999)
    {
    for(i=1;i<SI;i++)
    {
        array[i]=atoi(argv[i]);
        n=n+1;
        if(atoi(argv[i])==999)
        break;

    }
    }
    
    for(i=1;i<n;i++){
    printf("%d\n",array[i]);}
    sum=sum_of_num(array,n);
    printf("the sum of number is %d\n",sum);
    average=average_of_num(sum,n);
    printf("the average is %f\n",average);
    product=product_of_num(array,n);
    printf("product of number is %f",product);
    return 0;
}



int sum_of_num(int array[],int n)
{
    int sum=0;
    for(i=1;i<n;i++)
    {
        sum+=array[i];
    }
    return sum;
}



float average_of_num(int sum,int n)
{
    float average=0;
    average=sum/(n-1);
    return average;
}



float product_of_num(int array[],int n)
{
    float product=1;
    for(i=1;i<n;i++)
    {
        product*=array[i];
    }
    return product;
}
