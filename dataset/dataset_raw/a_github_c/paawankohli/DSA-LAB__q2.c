#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
}node;

typedef struct
{
    node* s[MAX];
    int tos;
}STACK;

void push(STACK *s, node* n)
{
    s->s[++(s->tos)] = n;
}

node* pop(STACK *s)
{
    return s->s[(s->tos)--];
}

typedef struct
{
    node* c[MAX];
    int front;
    int rear;
}queue;

void InsertQ(queue *q, node* n)
{
    if (q->rear == MAX)
        printf("Side Full\n");
    
    else
        q->c[(q->rear)++]=n;
}

int QIsEmpty(queue *q)
{
    if (q->front == q->rear)
        return 1;
    else
        return 0;
}

node* DeleteQ(queue *q)
{
    return q->c[(q->front)++];
}

node* create()
{
    node *p;
    int x;
    printf("Enter data(-1 for no data):");
    scanf("%d", &x);
    
    if (x == -1)
        return NULL;
    
    p = (node*)malloc(sizeof(node));
    p->data = x;
    
    printf("Enter left child of %d:\n", x);
    p->left = create();
    printf("Enter right child of %d:\n", x);
    p->right = create();
    
    return p;
}

void levelorder(node* root) 
{
    queue q;
    q.front = MAX/2;
    q.rear = MAX/2;

    InsertQ(&q, root);
    
    while (!QIsEmpty(&q)) 
    {
        node* temp = DeleteQ(&q);
        printf("%d\t", temp->data);
    
        if (temp->left) 
            InsertQ(&q, temp->left);
        
        if (temp->right) 
            InsertQ(&q, temp->right);
    }
}

void inorder(node *t)
{
    node* curr;
    curr = t;
    STACK s;
    s.tos = -1;
    
    push(&s, t);
    curr = curr->left;
    
    while (s.tos != -1 || curr != NULL)
    {
        while (curr != NULL)
        {
            push(&s, curr);
            curr = curr->left;
        }
    
        curr = pop(&s);
        printf("%d\t", curr->data);
        curr = curr->right;
    }
}

void preorder(node *t)
{
    node* curr;
    STACK s;
    
    s.tos = -1;
    
    push(&s, t);
    
    while (s.tos != -1)
    {
        curr = pop(&s);
        printf("%d\t", curr->data);
    
        if (curr->right)
            push(&s, curr->right);

        if (curr->left)
            push(&s, curr->left);
    }
}

void postorder(node *t)
{
    STACK s;
    node*curr;
    curr = t;
    s.tos = -1;
    
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
            printf("%d\t", curr->data);
            curr = NULL;
        }
    
    }while (s.tos != -1);
}

int main()
{
    node *root;
    root = create();

    printf("\nThe inorder traversal of tree is:\n");
    inorder(root);

    printf("\nThe postorder traversal of tree is:\n");
    postorder(root);

    printf("\nThe levelorder traversal of tree is:\n");
    levelorder(root);

    printf("\nThe preorder traversal of tree is:\n");
    preorder(root);

    return 0;
}