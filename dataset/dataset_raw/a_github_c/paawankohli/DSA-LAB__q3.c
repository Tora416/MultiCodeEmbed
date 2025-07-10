#include<stdio.h>
#include<stdlib.h>
#define MAX 10
#define size 20
#include <math.h>

typedef struct node
{
    char data;
    struct node *left;
    struct node *right;
}node;

typedef struct
{
    node* s[MAX];
    int tos;
}STACK;

node* newNode(int v)
{
    node *temp = (node*)malloc(sizeof(node));
    temp->left = temp->right = NULL;
    temp->data = v;
    return temp;
}

typedef struct
{
    float a[size];
    int tos;
} STACKs;

void pushs(STACKs *s, float x)
{
    s->a[++(s->tos)] = x;
}

float pops(STACKs *s)
{
    return s->a[(s->tos)--];
}

void push(STACK *s, node* n)
{
    s->s[++(s->tos)] = n;
}

node* pop(STACK *s)
{
    return s->s[(s->tos)--];
}

void inorder(node* root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%c ", root->data);
    inorder(root->right);
}

float calcu(node *root)
{
    node* curr;
    curr = root;
    
    STACK s;
    STACKs expression;
    s.tos = -1;
    expression.tos = -1;
    
    char m;
    float p, q;
    
    do
    {
        while (curr != NULL)
        {
            if (curr->right != NULL)
                push(&s, curr->right);
    
            push(&s, curr);
            curr = curr->left;
        }
    
        curr = pop(&s);
    
        if (curr->right != NULL && s.s[s.tos] == curr->right)
        {
            pop(&s);
            push(&s, curr);
            curr = curr->right;
        }
        else
        {
            m = curr->data;

            switch (m)
            {
                case '*':   pushs(&expression, pops(&expression)*pops(&expression));
                            break;
                
                case '/':   pushs(&expression, pops(&expression) / pops(&expression));
                            break;
                
                case '-':   pushs(&expression, pops(&expression) - pops(&expression));
                            break;
        
                case '+':   pushs(&expression, pops(&expression) + pops(&expression));
                            break;
        
                case '$':   p = pops(&expression);
                            q = pops(&expression);
                            pushs(&expression, pow(p, q));
                            break;

                default:    pushs(&expression, (float)(m - '0'));
                            break;
            }
            curr = NULL;
        }
    }while (s.tos != -1);
    
    return expression.a[0];
}

int isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return 1;
    else
        return 0;
}

node* constructTree(char postfix[])
{
    STACK st;
    st.tos = -1;
    node *t, *t1, *t2;
    
    int i, j;
    
    for (j = 0; postfix[j] != '\0'; j++);
    
    for (i = 0; i < j; i++)
    {
        if (!isOperator(postfix[i]))
        {
            t = newNode(postfix[i]);
            push(&st, t);
        }
        else
        {
            t = newNode(postfix[i]);
            t2 = pop(&st);
            t1 = pop(&st);

            t->right = t2;
            t->left = t1;

            push(&st, t);
        }
    }

    return t;
}

int main()
{
    char postfix[MAX];
    scanf(" %s", postfix);
    node* r = constructTree(postfix);

    printf("infix expression is \n");
    inorder(r);

    printf("\n%.2f", calcu(r));
    return 0;
}