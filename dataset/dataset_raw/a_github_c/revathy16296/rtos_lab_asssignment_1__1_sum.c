#include<stdio.h>
#include<stdlib.h>
#define SI 10

float sum_of_num(int array[]);
float average_of_num(float sum);
float product_of_num(int array[]);

int i;



int main()
{
    int array[SI];
    float product,average,sum;
    printf("enter the array elements\n");
    for(i=0;i<SI;i++)
    {
        scanf("%d",&array[i]);
    }
    sum=sum_of_num(array);
    printf("the sum of number is %f\n",sum);
    average=average_of_num(sum);
    printf("the average is %f\n",average);
    product=product_of_num(array);
    printf("product of number is %f",product);
    return 0;
}



float sum_of_num(int array[])
{
    float sum=0;
    for(i=0;i<SI;i++)
    {
        sum+=array[i];
    }
    return sum;
}



float average_of_num(float sum)
{
    float average=0;
    average=sum/SI;
    return average;
}



float product_of_num(int array[])
{
    float product=1;
    for(i=0;i<SI;i++)
    {
        product*=array[i];
    }
    return product;
}



    





    
