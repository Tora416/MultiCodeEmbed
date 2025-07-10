#define MAX 10
#define true 1
#define false 0

typedef struct 
{
    char item[MAX];
    int top;
}stack;

void isFull()
{
    printf("\nError! Stack is full!\n");
}

int isEmpty()
{
    printf("\nError ! Stack is empty!\n")
}

void push(stack* ps, char x)
{
    if(ps->top == MAX - 1)
        isFull();
    else
        ps->item[++(ps->top)] = x;
}

char pop(stack* ps)
{
    if(ps->top > -1)
        return ps->item[(ps->top)--];
    else
    {
        isEmpty();  
        return '\0';
    }
}

void display(stack* ps)
{
    if(ps->top > -1)
    {
        for(int i = 0 ; i < ps->top ; i++)
            printf("%d  ", ps->item[i]);
    }
}

int main()
{
    printf()
}

