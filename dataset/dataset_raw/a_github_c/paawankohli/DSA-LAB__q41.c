#include <stdio.h>
#include <string.h>

typedef struct
{
    char a[20][20];
    int tos;
}stack;

void push(stack *s, char a[])
{
    strcpy(s->a[(++s->tos)], a);
}

void pop(stack * s, char temp[])
{
    strcpy(temp, s->a[(s->tos)--]);
}

int alnum(char t)
{
    switch(t)
    {
        case '+':
        case '-':
        case '/':
        case '*':
        case '$':
                    return 0;
    }

    return 1;
}

int main()
{
    stack s;
    s.tos = -1;
    char pre[20], pos[20], t;

    printf("Enter prefix: ");
    scanf("%s", pre);

    int i, j;

    int l = strlen(pre);

    for(int i = 0 ; i < l ; i++)
    {
        t = pre[i];
        char temp[2] = {t, '\0'};

        push(&s, temp);

        while (alnum(s.a[s.tos][0]) && alnum(s.a[(s.tos - 1)][0]) && s.tos != 0)
        {
            char temp1[20], temp2[20], temp3[20];
            pop(&s, temp1);
            pop(&s, temp2);
            pop(&s, temp3);

            strcat(temp2, temp1);
            strcat(temp2, temp3);
            push(&s, temp2);
        }
    }

    strcpy(pos, s.a[0]);

    printf("Postfix expression is %s", pos);
}
