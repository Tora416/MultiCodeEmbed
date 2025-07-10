#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m;
    int n;

    printf("digite o primeiro numero: ");
    scanf("%d",&m);

    printf("digite o segundo numero: ");
    scanf("%d",&n);

while ( m!=n)

{

if (m > n){

    m = m - n;

}else

    n = n - m;

}
    printf("o maximo divisor comum eh:%d", m);
}




