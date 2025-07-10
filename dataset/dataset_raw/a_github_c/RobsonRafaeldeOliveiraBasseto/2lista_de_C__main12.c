#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    int b;
    int c = 2;
    int d;

    printf("Digite um numero: ");
    scanf("%d",&a);

    for(b = 0; b <= a; b++)
    {
        if(a>=0)
        {
            d = a / c;
            c++;
        }if(a % c == 0)
        {
            printf("%d / %d = %d\n",a,c,d);
        }

    }




}
