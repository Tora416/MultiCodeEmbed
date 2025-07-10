#include <stdio.h>
#include "charStack.h"
#include <string.h>



void strrev(char *str)
{
    int i = strlen(str) - 1, j = 0;

    char ch;
    
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        
        i--;  j++;
    }
    
}

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

    strrev(exp);        
                        


    for(int i = 0 ; exp[i] != '\0' ; i++)
    {
        char token = exp[i];

        if (token >= '0' && token <= '9')
            push(&s, token);
        
        else
        {
            char a = pop(&s);                       
            char b = pop(&s);

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