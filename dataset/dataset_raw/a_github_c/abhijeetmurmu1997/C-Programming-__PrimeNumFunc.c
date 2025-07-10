#include<stdio.h>
int checkPrime(int n);
int main()
{
    int l,u,check,temp,i;
    printf("enter l and u:\n");
    scanf("%d%d",&l,&u);
    if(l>u)
    {
        temp = l;
        l = u;
        u = temp;
    }
    for(i = l;i <= u;i++)
    {
        if(i == 1 || i == 0)
        continue;
        check = 0;
        check = checkPrime(i);
        if(check == 0)
        {
           printf("%d\n",i);
        } 
    }
    return 0;
}
int checkPrime(int n)
{
    int flag = 0,j;
    for (j = 2;j <= n/2; j++)
    {
        if(n%j == 0)
        {
           flag = 1;
           break;
        }
    }
    return flag;
}
