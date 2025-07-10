

#include<stdio.h>
int factorial(int number);
void main()
{
    float sum=0.0f;
    int n=0;
    int i=0;
        
    printf("Enter the value of n: ");
    scanf("%d", &n);
    for(i=1; i<=n; i++)
    {
        sum = sum + (factorial(i)/i);   
    }
    
    
    printf("Sum = %f", sum);    
}

int factorial(int number)
{
    int copy=number;
    int i=0;
    int fact=1;
    
    for(i=1; i<=copy; i++)
    {
        fact = fact * i;
    }
    
    return fact;
}
