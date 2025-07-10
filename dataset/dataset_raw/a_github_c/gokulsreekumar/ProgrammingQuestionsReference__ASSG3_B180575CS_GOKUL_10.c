#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct stack{
    int top;
    int cap;
    char* A;
};

int StackOverflow(struct stack* stk)
{
    if(stk->top==stk->cap-1)
        return 1;
    else 
        return 0;
}
int StackEmpty(struct stack* stk)
{
    if(stk->top==-1)
        return 1;
    else
        return 0;
}
void push(struct stack* stk, char elem){
    if(StackOverflow(stk))
    {
        printf("%d\n", 999);
        return;
    }
    stk->top++;
    stk->A[stk->top]=elem;
        
};
char pop(struct stack* stk){
    if(StackEmpty(stk))
    {
        printf("%d\n", -1);
        return('b');
    }
    stk->top--;
    return(stk->A[stk->top+1]);
};


int isMatchingPair(char character1, char character2) 
{ 
   if (character1 == '(' && character2 == ')') 
     return 1; 
   else if (character1 == '{' && character2 == '}') 
     return 1; 
   else if (character1 == '[' && character2 == ']') 
     return 1; 
   else
     return 0; 
} 


int checkParantheses(char* exp,struct stack* stk)
{
    int i;char popped;
    for(i=0;i<stk->cap;i++)
    {
        if(exp[i]=='('||exp[i]=='{'||exp[i]=='[')
        {
            push(stk,exp[i]);
        }
        else if(exp[i]==')'||exp[i]=='}'||exp[i]==']')
        {
            popped=pop(stk);
            if(!(isMatchingPair(popped,exp[i])))
            {
                return 0;
            }
        }
    }
    return 1;
}

int main()
{

    char sel;
    int p;
    FILE* fp1;
    FILE* fp2;
    fp1=fopen("input.txt","r"); 
    fp2=fopen("output.txt","w");    
    char exp[10000];        
    while(1)    
    {
        int i=0;
        fscanf(fp1,"%c",&sel);
        if(sel=='e')
        {
            fgetc(fp1);
            fscanf(fp1,"%[^\n]",exp);
            i=strlen(exp);
            fgetc(fp1);
            struct stack* stk=(struct stack*)malloc(sizeof(struct stack));
            stk->A=(char*)malloc(i);
            stk->top=-1;
            stk->cap=i;
            
            p=checkParantheses(exp,stk);
            if(p==0)
            {
                fprintf(fp2, "NO\n");
            }
            else
                fprintf(fp2,"YES\n");
        }
        else if(sel=='s')
            break;
    }

}















