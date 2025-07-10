#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include "charStack.h"



int isOperand(char ch)      
{ 
    return (ch >= 'a' && ch <= 'z');
} 

int prec(char ch)           
{ 
    if (ch == '+' || ch == '-')
        return 1; 

    if (ch == '*' || ch == '/')
        return 2; 

    if (ch == '^')
        return 3;  
    
    return -1; 
} 

int infixToPostfix(char* exp, char* ans) 
{ 
    int i, k = 0; 

    stack s;

    for (i = 0 ; exp[i] != '\0' ; i++) 
    { 
    
        if (isOperand(exp[i]))      
            ans[k++] = exp[i]; 
        
        else if (exp[i] == '(')     
            push(&s, exp[i]); 
        
        else if (exp[i] == ')')     
        { 
            while (!isEmpty(&s) && top(&s) != '(') 
                ans[k++] = pop(&s); 
            
            pop(&s);  
        } 
        
        else            
        { 
            while ( !isEmpty(&s) && prec(exp[i]) <= prec(top(&s)) ) 
                ans[k++] = pop(&s); 
            
            push(&s, exp[i]); 
        } 
    } 

    while (!isEmpty(&s))            
        ans[k++] = pop(&s); 

    ans[k- 1] = '\0';  
} 

int main() 
{ 
    char exp[100], ans[100];
    scanf("%s", exp);   
    
    infixToPostfix(exp, ans);

    printf("%s \n", ans); 
} 