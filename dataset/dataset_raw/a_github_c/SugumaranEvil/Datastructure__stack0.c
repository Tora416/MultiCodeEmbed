







#include "stack.h"

#define MAX 5

int count = -1;
int arr[MAX];


int full(void);
int empty(void);


void push(int data)
{
    if(full())
    {
        
        printf("Stack is full\n");
    }
    else
    {
        
        count++;
        arr[count]=data;
    }
}


void pop(void)
{
    if(empty())
    {
        
        printf("Stack is empty\n");
    }
    else
    {
        
        count = count-1;
    }
}


int full()
{
    if(count == (MAX-1))
        return 1;
    else
        return 0;
}


int empty()
{
    if(count == -1)
        return 1;
    else
        return 0;

}

int main()
{
    
    push(10);
    push(11);
    push(12);
    push(13);
    push(14);

    printf("Before pop\n");
    int i;
    for(i=0;i<count+1;i++)
        printf("%d\n",arr[i]);

    
    pop();
    printf("After pop\n");
    for(i=0;i<count+1;i++)
        printf("%d\n",arr[i]);
}
