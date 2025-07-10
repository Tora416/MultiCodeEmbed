

#include <stdio.h>
void swapval(int a , int b)
{
    int t = a;
    a = b;
    b = t;
    printf("\n\nAfter swapping by value : \n");
    printf("Value of a : %d\nValue of b : %d", a, b);
}
void swapref(int *a , int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int main()
{
    int a, b ;
    printf("Enter 2 variables a & b: ");
    scanf("%d%d", &a, &b);
    printf("Value of a : %d\nValue of b : %d", a, b);
    swapval(a, b);

    swapref(&a, &b);
    printf("\n\nAfter swapping by reference : \n");
    printf("Value of a : %d\nValue of b : %d", a, b);
    printf("\n");
}