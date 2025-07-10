#include<stdio.h>

struct complex{
    float real;
    float imag;
}complex;

struct complex add(struct complex n1,struct complex n2);
struct complex subtract(struct complex n1,struct complex n2);
struct complex multiply(struct complex n1,struct complex n2);
int main()
{
    struct complex n1,n2,result,result1,result2;
    
    printf("For 1st complex number \n");
    printf("Enter the real parts : ");
    scanf("%f",&n1.real);
    printf("Enter the imaginary parts : ");
    scanf("%f",&n1.imag);
    printf("\nFor 2nd complex number \n");
    printf("Enter the real parts : ");
    scanf("%f",&n2.real);
    printf("Enter the imaginary parts : ");
    scanf("%f",&n2.imag);
    printf("\n");
    
    result=add(n1,n2);
    printf("Sum value = %.1f + %.1fi\n", result.real, result.imag);
    result1=subtract(n1,n2);
    printf("Subtraction value = %.1f - %.1fi\n", result1.real, result1.imag);
    result2=multiply(n1,n2);
    printf("Multiply value = %.1f - %.1fi\n", result2.real, result2.imag);
}
struct complex add(struct complex n1,struct  complex n2) {
   struct  complex temp;
    temp.real = n1.real + n2.real;
    temp.imag = n1.imag + n2.imag;
    return (temp);
}
struct complex subtract(struct complex n1, struct complex n2) {
    struct complex temp1;
    temp1.real = n1.real - n2.real;
    temp1.imag = n1.imag - n2.imag;
    return (temp1);
}
struct complex multiply(struct complex n1, struct complex n2) {
    struct complex temp2;
    temp2.real = n1.real * n2.real;
    temp2.imag = n1.imag * n2.imag;
    return (temp2);
}