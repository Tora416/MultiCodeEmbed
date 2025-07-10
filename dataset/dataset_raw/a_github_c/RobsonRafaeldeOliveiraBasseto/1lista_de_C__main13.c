#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    int b;
    int c;

    printf("Digite o primeiro numero: ");
    scanf("%d",&a);

    printf("Digite o segundo numero: ");
    scanf("%d",&b);

    printf("Digite o terceiro numero: ");
    scanf("%d",&c);

    if

    ((a>b) && (b>c)){
    printf ("%d,%d,%d", c,b,a);
    }
    if

    ((a>b) && (c>b)){
    printf ("%d,%d,%d", b,c,a);
    }
    if

    ((b>a) && (a>c)){
    printf ("%d,%d,%d", c,a,b);
    }
    if

    ((b>c) && (c>a)){
    printf ("%d,%d,%d", a,c,b);
    }
    if

    ((c>b) && (b>a)){
    printf ("%d,%d,%d", a,b,c);
    }
    if

    ((c>a) && (a>b)){
    printf ("%d,%d,%d", b,a,c);
    }
}

