#include<stdio.h>
#define MAX 999
int fibonnaciSeries();
int primeSeries();
int main()
{
    int n;
    scanf("%d",&n);
    if(n%2 == 1)
    {
        fibonnaciSeries(n/2 + 1);
    }
    else
    primeSeries(n/2);
}
int fibonnaciSeries(int x)
{
    int a=0,b=1,temp;
    int i;
    for(i=1;i<=x;i++)
    {
        temp = a+b;
        a = b;
        b = temp;
    }
    printf("%d",a);
}
int primeSeries(int y)
{
    int i,j,flag,count = 0;
    for(i=2;i<=MAX;i++)
    {
        flag = 0;
        for(j=2;j<i;j++)
        {
            if(i%j == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            if(++count == y)
            {
                printf("%d",i);
            }
        }
    }
}
