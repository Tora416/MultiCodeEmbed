

#include<stdio.h>
int isPalindrome(int number);

void main()
{
    int n;
    printf("Enter any number:\n");
    scanf("%d", &n);
    
    if(isPalindrome(n) == 1)
        printf("%d is a Palindrome...\n", n);
        
    else
        printf("%d is NOT a Palindrome...\n", n);
}

int isPalindrome(int number)
{
    int copy=number;
    int sum=0;
    
    while(copy != 0)
    {
        sum = sum*10 + (copy%10);
        copy /= 10;
    }
    
    if(sum == number)
        return 1;
    else
        return 0;
}
