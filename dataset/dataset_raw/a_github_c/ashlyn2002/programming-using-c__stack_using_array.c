

#include <stdio.h>
#include <stdlib.h>
int stack[50],N;
int top=-1;
void push();
void pop();
void peek();
void display();
void isfull();
void isempty();
int main()
{
    printf("THE STACK USING THE ARRAY\n");
    printf("enter the size of the array(max size of the array is 50)= \n");
    scanf("%d",&N);
    printf("1.push\n2.pop\n3.peek\n4.display\n5.is full\n6.is empty\n7.exit\n");
    int choice;
    do
    {
        printf("enter the choice= ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:printf("insert the element to the stack\n");
            push();
            break;
            case 2:printf("delete the element from the stack\n");
            pop();
            break;
            case 3:printf("display the top element in the stack\n");
            peek();
            break;
            case 4:printf("display all the element in the stack\n");
            display();
            break;
            case 5:printf("checking the stack is full or not\n");
            isfull();
            break;
            case 6:printf("checking the stack is empty or not\n");
            isempty();
            break;
            case 7:printf("exit \n");
            break;
            default:printf("wrong choice\n");
            break;
        }
    }while(choice!=7);
    return 0;
}
void push()
{
    int x;
    printf("enter the data =");
    scanf("%d",&x);
    if(top==N-1)
    {
        printf("stack overflow\n");
    }
    else
    {
        top++;
        stack[top]=x;
    }
}
void pop()
{
    if(top==-1)
    {
        printf("stack under flow\n");
    }
    else
    {
        top--;
    }
}
void peek()
{
    if(top==-1)
    {
        printf("there is no element in the stack\n");
    }
    else
    {
        printf("the top most element in the stack is %d\n",stack[top]);
    }
}
void display()
{
    int i;
    if(top>-1)
    {
        for(i=top;i>=0;i--)
        {
            printf("%d\t",stack[i]);
        }
        printf("\n");
    }
    else
    {
        printf("the stack is empty\n");
    }
}
void isfull()
{
    if(top==N-1)
    {
        printf("the stack is full\n");
    }
    else
    {
        printf("the stack is not full\n");
    }
}
void isempty()
{
    if(top==-1)
    {
        printf("the stack is empty\n");
    }
    else
    {
        printf("the stack is not empty\n");
    }
}
