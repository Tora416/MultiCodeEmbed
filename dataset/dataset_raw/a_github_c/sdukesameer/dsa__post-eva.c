
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50
typedef struct
{
    int top;
    unsigned int size;
    float* arr;
}stack;
stack* createStack(unsigned int x)
{
    stack* ret=(stack*) malloc(sizeof(stack));
    ret->top=-1;
    ret->size=x;
    ret->arr=(float*) malloc(x * sizeof(float));
    return ret;
}
float c2i(char x)
{
    return (int)x - (int)'0';
}
void push(stack* stk, float n)
{
    stk->arr[++(stk->top)]=n;
}
float pop(stack* stk)
{
    return stk->arr[stk->top--];
}
int isOperator(char ch)
{
    if (ch=='+' || ch=='-' || ch=='*' || ch=='/')
        return 1;
    else
        return 0;
}
float operation(float f, char x, float s)
{
    if (x=='+')
        return f+s;
    if (x=='-')
        return f-s;
    if (x=='*')
        return f*s;
    else
        return f/s;
}
float evaluatePostfix(char exp[])
{
    stack* stk=createStack(strlen(exp));
    int i=0;
    float f=0,s=0,t=0;
    while (exp[i]!='\0')
    {
        if((exp[i]==',' && exp[i+1]==',') || (exp[i]==' ' && exp[i+1]==' '))
            i++;
        else if((exp[i]==',' && exp[i+1]==' ') || (exp[i]==' ' && exp[i+1]==','))
        {
            printf("Invalid operator or operand encountered.\n");
            return 0;
        }
        else if((int)exp[i]>47 && (int)exp[i]<58)
            t=(t*10)+c2i(exp[i]);
        else if(exp[i]==',' || exp[i]==' ')
        {
            push(stk,t);
            t=0;
        }
        else if(isOperator(exp[i]))
        {
            if(stk->top-2<-1)
            {
                printf("Underflow, not enough operands.\n");
                return 0;
            }
            s=pop(stk);
            f=pop(stk);
            push(stk,operation(f,exp[i],s));
            if(i+1<stk->size)
                i++;
        }
        else
        {
            printf("Invalid operator or operand encountered.\n");
            return 0;
        }
        i++;
    }
    if(stk->top!=0)
    {
        printf("Overflow, too may operands.\n");
        return 0;
    }
    return stk->arr[stk->top];
}
int main()
{
    while(1)
    {
        char exp[MAX+1];
        printf("\nTo exit enter a blank expression.\n");
        printf("Enter a postfix expression: ");
        gets(exp);
        if(strlen(exp)>50){
            printf("Overflow, expression length greater than 50.\n");
            break;
        }
        else if(strlen(exp)==0){
            printf("No expression found.\n");
            break;
        }
        else
        { 
            float ans=evaluatePostfix(exp);
            if(ans)
                printf("Postfix Evaluation: %.2f\n",ans);
        }
    }
    return 0;
}