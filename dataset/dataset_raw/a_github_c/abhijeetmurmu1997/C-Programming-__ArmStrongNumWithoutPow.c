#include<stdio.h>
int power();
int main()
{
    int n;
    int count = 0;
    printf("enter a number:");
    scanf("%d",&n);
    int temp = n;
    while(temp!=0)
    {
        count++;
        temp/=10;
    }
    printf("count:%d\n",count);
    int rem = 0, sum = 0;
    int t = n;
    int i;
    while(t!=0)
    {
        int mul=1;
        rem = t%10;
        for(i=1;i<=count;i++)
        {
            mul = mul*rem;
        }
        printf("Power of %d is : %d\n",rem,mul);
        sum = sum+mul;
        t = t/10;   
    }
    if(sum == n)
    {
        printf("ARMSTRONG NUMBER");
    }
    else
    printf("NOT ARMSTRONG NUMBER");
    return 0;
}
