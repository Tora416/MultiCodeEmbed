#include <stdio.h>
#define MAX 10

typedef struct
{
    int a[MAX];
    int tos1;
    int tos2;
}stack;

void push1(stack *s)
{
    if(s->tos2 - s->tos1 == 1)
        printf("Array Full");
    else
    {
        printf("Push: ");
        int ele;
        scanf("%d", &ele);
        s->a[++(s->tos1)] = ele;
    }
}

void push2(stack *s)
{
    if(s->tos2 - s->tos1 == 1)
        printf("Array Full");
    else
    {
        printf("Push: ");
        int ele;
        scanf("%d", &ele);
        s->a[--(s->tos2)] = ele;
    }
}

void pop1(stack *s)
{
    if (s->tos1 == -1)
        printf("Underflow! \n");
    else
        printf("%d popped\n", s->a[(s->tos1)--]);
}

void pop2(stack *s)
{
    if (s->tos2 == MAX)
        printf("Underflow! \n");
    else
        printf("%d popped\n", s->a[(s->tos2)++]);
}

void display(stack *s)
{
    printf("\nStack 1: ");
    for(int i = 0 ; i <= s->tos1 ; i++)
        printf("%d ", s->a[i]);

    printf("\nStack 1: ");
    for(int i = MAX - 1 ; i >= s->tos2 ; i--)
        printf("%d ", s->a[i]);

    printf("\n");


}

int main()
{
    stack s;
    s.tos2 = MAX;
    s.tos1 = -1;

    int z = 0, k;

    while (z == 0)
    {
        printf("1. Push1   2. Push2   3. Pop1    4. Pop2    5. Display    6. Exit \n");
        scanf("%d", &k);

        switch(k)
        {
            case 1: push1(&s); break;
            case 2: push2(&s); break;
            case 3: pop1(&s); break;
            case 4: pop2(&s); break;
            case 5: display(&s); break;
            case 6: z = 1;
        }
    }
}
