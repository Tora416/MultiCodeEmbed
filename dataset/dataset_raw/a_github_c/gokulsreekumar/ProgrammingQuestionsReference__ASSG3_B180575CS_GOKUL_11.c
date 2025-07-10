#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
 
struct Stack 
{ 
    int top; 
    unsigned capacity; 
    int* array; 
}; 
  
struct Stack* createStack( unsigned capacity ) 
{ 
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack)); 
  
    if (!stack)  
        return NULL; 
  
    stack->top = -1; 
    stack->capacity = capacity; 
  
    stack->array = (int*) malloc(stack->capacity * sizeof(int)); 
  
    if (!stack->array) 
        return NULL; 
    return stack; 
} 
int isEmpty(struct Stack* stack) 
{ 
    return stack->top == -1 ; 
} 
char peek(struct Stack* stack) 
{ 
    return stack->array[stack->top]; 
} 
char pop(struct Stack* stack) 
{ 
    if (!isEmpty(stack)) 
        return stack->array[stack->top--] ; 
    return '$'; 
} 
void push(struct Stack* stack, char op) 
{ 
    stack->array[++stack->top] = op; 
} 
  
int isOperand(char ch) 
{ 
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'); 
} 
  
int Prec(char ch) 
{ 
    switch (ch) 
    { 
    case '+': 
    case '-': 
        return 1; 
  
    case '*': 
    case '/': 
        return 2; 
  
    case '^': 
        return 3; 
    } 
    return -1; 
} 
  
void infixToPostfix(char* exp) 
{ 
    int i, k; 
  
    struct Stack* stack = createStack(strlen(exp));  

    for (i = 0, k = -1; exp[i]; ++i) 
    { 
 
        if (isOperand(exp[i])) 
            exp[++k] = exp[i]; 
          
        else if (exp[i] == '(') 
            push(stack, exp[i]); 
          

        else if (exp[i] == ')') 
        { 
            while (!isEmpty(stack) && peek(stack) != '(') 
                exp[++k] = pop(stack); 
            if (!isEmpty(stack) && peek(stack) != '(') 
                return;             
            else
                pop(stack); 
        } 
        else
        { 
            while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack))) 
                exp[++k] = pop(stack); 
            push(stack, exp[i]); 
        } 
  
    } 

    while (!isEmpty(stack)) 
        exp[++k] = pop(stack); 
  
    exp[++k] = '\0'; 
} 

int main(int argc,char *argv[])
{
    char ch,temp;
    char exp[10000];
    FILE *fp1;
    FILE *fp2;
    fp1=fopen("input.txt","r");
    fp2=fopen("output.txt","w");
    while(1)
         {
            fscanf(fp1,"%c",&ch);
            if(ch=='e')
            {
                fgetc(fp1);
                fscanf(fp1,"%[^\n]",exp);
                infixToPostfix(exp);
                fprintf(fp2,"%s\n",exp);
            }
            else if(ch=='s')
                break;

        }

    fclose(fp1);
    fclose(fp2);
    return 0;
}
