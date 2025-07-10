#include<stdio.h>
#include<stdlib.h>
int GCD(int a ,int b)
{
    int c;
    int opcount=0;
    if(b<a)
    {   
        a=a^b;
        b=a^b;
        a=a^b;
    }
    c=a;
    while(1)
    {
        opcount++;
        if(a%c==0 && b%c==0)
        {
            printf("opcount: %d\n",opcount);
            return c;
        }
        c-=1;
    }

}

int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    printf("%d\n",GCD(a,b));
    return 0;
}