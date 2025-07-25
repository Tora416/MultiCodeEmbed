
#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 100


int top = -1;
char stack[CAPACITY];

void push(char item)
{
    if(top>= CAPACITY-1)
    {
        printf("Stack is Full\n");
    }
    else
    {
        top++;
        stack[top] = item;
    }
}
char pop()
{
    char item;
    item = stack[top];
    top--;
    return(item);
}
int precedence(char symbol)
{
    if(symbol == '^')
        return 3;
    else if(symbol == '*' || symbol == '/')
        return 2;
    else if(symbol == '+' || symbol == '-')
        return 1;
    else
        return 0;
}
int is_operator(char symbol)
{
    if(symbol == '^' || symbol == '/' || symbol == '*' || symbol == '+' || symbol == '-')
        return 1;
    else
        return 0;
}


int main()
{
    char infix[CAPACITY], postfix[CAPACITY], item, temp;
    int i = 0, j = 0;
    printf("Enter an Infix Expression to Convert into Postfix : ");
    gets(infix);

    while(infix[i]!='\0')
    {
        item = infix[i];
        if(item == '(')
        {
            push(item);
        }
        else if((item >= 'A' && item <= 'Z') || (item >= 'a' && item <= 'z'))
        {
            postfix[j] = item;
            j++;
        }
        else if(is_operator(item) == 1)
        {
            temp = pop();
            while(is_operator(temp) == 1 && precedence(temp) >= precedence(item))
            {
                postfix[j] = temp;
                j++;
                temp = pop();
            }
            push(temp);
            push(item);
        }
        else if(item == ')')
        {
            temp = pop();
            while(temp != '(')
            {
                postfix[j] = temp;
                j++;
                temp = pop();
            }
        }
        else
        {
            printf("\nInvalid Expression");
        }
        i++;
    }
    while(top > -1)
    {
        postfix[j] = pop();
        j++;
    }
    printf("\nArithmetic Expression in Postfix form is : ");
    puts(postfix);
    return 0;
}
