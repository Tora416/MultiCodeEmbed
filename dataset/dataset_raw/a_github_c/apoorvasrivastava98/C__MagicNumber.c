
#include<stdio.h>
void magic(int);
void main()
{
    int n;
    printf("Enter the number to be checked \n");
    scanf("%d",&n);
    magic(n);
}
void magic(int n)
{
    int i,sum=0,num=n;
        while (n > 0 || sum > 9) 
    { 
        if (n == 0) 
        { 
            n = sum; 
            sum = 0; 
        } 
        sum =sum + n % 10; 
        n = n / 10; 
    } 
     if(sum==1)
     {
         printf("%d is a magic number",num);
     }
     else
     {
         printf("%d is not a magic number",num);
     }
}
