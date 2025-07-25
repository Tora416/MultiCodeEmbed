
#include<stdio.h>
#include<stdlib.h>
typedef struct
{
    int top;
    unsigned int size;
    int* arr;
}stack;
stack* createstack(unsigned int x)
{
    stack* ret=(stack* ) malloc(sizeof(stack));
    ret->top=-1;
    ret->size=x;
    ret->arr=(int* )malloc(x * sizeof(int));
    return ret;
}
int is_full(stack* stk)
{
    if(stk->top==(stk->size-1))
        return 1;
    else
        return 0;
}
void push(stack* stk, int n)
{
    if(is_full(stk))
        printf("OVERFLOW!\n");
    else
    {
        stk->arr[++stk->top]=n;
        printf("%d pushed to stack.\n",stk->arr[stk->top]);
    }
}
int is_empty(stack* stk)
{
    if(stk->top==-1)
        return 1;
    else
        return 0;
}
void pop(stack* stk)
{
    if(is_empty(stk))
        printf("STACK EMPTY!\n");
    else
        printf("%d popped from stack.\n",stk->arr[stk->top--]);
}
int main()
{
    int ch,x;
    printf("Enter size of the working Stack:\n");
    scanf("%d",&x);
    stack* stk=createstack(x);
    while(1)
    {
        printf("\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        if (ch==1)
        {
            int n;
            scanf("%d",&n);
            push(stk,n);
        }
        else if(ch==2)
            pop(stk);
        else if(ch==3)
        {
            printf("Exitting program, Thank you.\n");
            break;
        }
        else
            printf("Invalid, choice try again.\n");
    }
    return 0;
}