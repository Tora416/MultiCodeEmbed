#include<stdio.h>
#include<math.h>

void main()
{
    int number = 0;
    int count = 0;
    int copy = 0;
    int second_copy = 0;
    int sum = 0;

    printf("\nEnter any number: ");
    scanf("%d", &number);

    copy = number;
    second_copy = copy;
    while(copy != 0)
    {
        count++;
        copy /= 10;
    }

    
    while(second_copy != 0)
    {
        sum += pow((second_copy%10), count);
        second_copy /= 10;
    }

    if(sum == number)
        printf("\n%d is an Armstrong Number\n", number);

    else
        printf("\n%d is NOT an Armstrong Number\n", number);

}