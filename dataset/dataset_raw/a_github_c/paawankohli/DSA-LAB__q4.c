#include<stdio.h>
#include<stdlib.h>
#define MAX 10

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} node;

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

void inorder(node *t)
{
    if (t == NULL)
        return;

    inorder(t->left);
    printf("%d ", t->data);
    inorder(t->right);
}

node* copy(node *t)
{
    node *p;

    if (t == NULL)
        return NULL;

    p = (node*)malloc(sizeof(node));
    p->data = t->data;

    p->left = copy(t->left);
    p->right = copy(t->right);

    return p;
}

int Equal(node* root1, node* root2)
{
    return  (root1 == NULL && root2 == NULL) || ((root1 && root2 && root1 -> data == root2 -> data)
            && Equal(root1->left, root2->left) && Equal(root1->right, root2->right));
}

int main()
{
    node *root, *c;
    root = create();
    c = copy(root);

    printf("\nThe inorder traversal of copied tree is:\n");
    inorder(c);

    printf("\nThe inorder traversal of original tree is:\n");
    inorder(root);

    if(Equal(root, c))
        printf("\nEqual!\n");
    else
        printf("\nNot Equal!\n");
    
    return 0;
}