#include <stdio.h>
#include "charStack.h"



int toInt(char c)
{
    return c - '0';
}

int main()
{
    stack s;
    char exp[15];

    printf("Enter exp: ");
    scanf("%s", exp);

    for(int i = 0 ; exp[i] != '\0' ; i++)
    {
        char token = exp[i];

        if (token >= '0' && token <= '9')
            push(&s, token);
        
        else
        {
            char b = pop(&s);
            char a = pop(&s);

            switch(token)
            {
                case '+':   push(&s, toInt(a) + toInt(b) + '0');
                            break;

                case '-':   push(&s, toInt(a) - toInt(b) + '0');
                            break;

                case '/':   push(&s, toInt(a) / toInt(b) + '0');
                            break;

                case '*':   push(&s, toInt(a) * toInt(b) + '0');
                            break;
            }

        }
    }

    printf("Ans = %d \n", toInt(pop(&s)));
}
