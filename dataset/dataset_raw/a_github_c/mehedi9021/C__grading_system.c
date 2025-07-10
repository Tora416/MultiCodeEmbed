
#include<stdio.h>
int main()
{
    int n;
    printf("Enter The Number :");
    scanf("%d", &n);
    if (n>=80 && n<=100)
    {
        printf("\nEarned Grade is >> A+");
    }
    else if (n>=70 && n<=79)
    {
        printf("\nEarned Grade is >> A");
    }
    else if(n>=60 && n<=69)
    {
        printf("\nEarned Grade is >> A-");
    }
    else if (n>=50 && n<=59)
    {
        printf("\nEarned Grade is >> B");
    }
    else if (n>=40 && n<=49)
    {
        printf("\nEarned Grade is >> C");
    }
    else
    {
        printf("\nEarned Grade is >> F");
    }
    return 0;

}
