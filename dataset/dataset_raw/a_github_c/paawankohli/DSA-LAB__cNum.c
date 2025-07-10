#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int real;
    int imag;
} cNum;

cNum add(cNum a, cNum b)
{
    cNum temp;

    temp.real = a.real + b.real;
    temp.imag = a.imag + b.imag;

    return temp;
}

cNum subtract(cNum a, cNum b)
{
    cNum temp;

    temp.real = a.real - b.real;
    temp.imag = a.imag - b.imag;

    return temp;
}

cNum multiply(cNum a, cNum b)
{
    cNum temp;

    temp.real = a.real * b.real - a.imag * b.imag;
    temp.imag = a.imag * b.real + a.real * b.imag;

    return temp;
}

void display(cNum a)
{
    printf(" %d + %di \n", a.real, a.imag);
}

int main()
{
    cNum a, b, c;

    
    printf("Enter real and imaginary part of first number: ");
    scanf("%d %d", &a.real, &a.imag);

    printf("Enter real and imaginary part of second number: ");
    scanf("%d %d", &b.real, &b.imag);

    printf("Addition: ");
    display(add(a, b));

    printf("Subtract: ");
    display(subtract(a, b));

    printf("Multiply: ");
    display(multiply(a, b));

}


