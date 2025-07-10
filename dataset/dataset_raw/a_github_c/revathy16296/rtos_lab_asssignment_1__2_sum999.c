#include<stdio.h>
#include<stdlib.h>
#define SI 10

int sum_of_num(int array[],int n);
float average_of_num(int sum,int n);
float product_of_num(int array[],int n);

int i;



int main()
{
    int array[SI],n=0,sum;
    float product,average;
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
    for(i=0;i<n;i++)
    {
        sum+=array[i];
    }
    return sum;
}



float average_of_num(int sum,int n)
{
    float average=0;
    average=sum/n;
    return average;
}



float product_of_num(int array[],int n)
{
    float product=1;
    for(i=0;i<n;i++)
    {
        product*=array[i];
    }
    return product;
}
