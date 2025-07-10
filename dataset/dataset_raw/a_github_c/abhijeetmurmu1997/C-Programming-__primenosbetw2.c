#include<stdio.h>
int main()
{
    int low,high,i,temp,flag;
    printf("enter the lower number:");
    scanf("%d",&low);
    printf("enter the higher number:");
    scanf("%d",&high);
    if(low>high)
    {
        temp = low;
        low = high;
        high = temp;
    }
    while(low<high)
    {
        flag = 0;
        if(low<=1)
        {
            low++;
            continue;
        }
        for(i = 2;i <= low/2; i++)
        {
            if(low%i == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        printf("%d\n", low);
        low++;
    }
}
