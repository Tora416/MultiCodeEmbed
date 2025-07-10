#include <stdio.h>
#include <stdlib.h>

typedef struct node* nptr;
typedef struct node
{
    int data;
    nptr lchild, rchild;
}node;

nptr createNode(int x)
{
    nptr temp = (nptr)malloc(sizeof(node));
    temp->lchild = temp->rchild = NULL;
    temp->data = x;
    return temp;
}

nptr insertNode(nptr root, char path[])
{
    int i = 0;
    nptr parent = NULL, curr = root;

    while(curr && path[i])
    {
        parent = curr;

        if (path[i] == 'L')
            curr = parent -> lchild;
        else if (path[i] == 'R')
            curr = parent -> rchild;

        i++;
    }

    if (curr == NULL && path[i] == '\0')
    {
        printf("Path Found! Enter element: ");
        int x; scanf("%d", &x);

        if (path[i - 1] == 'R')
            parent -> rchild = createNode(x);
        else if (path[i - 1] == 'L')
            parent -> lchild = createNode(x);
    }
    else
        printf("Path error!");

    return root;
}

void inorder(nptr root)
{
    if (root == NULL)
        return;
    
    inorder(root->lchild);
    printf("%d ", root->data);
    inorder(root->rchild);
}

void preorder(nptr root)
{
    if (root == NULL)
        return;

    printf("%d ", root->data);
    preorder(root->lchild);
    preorder(root->rchild);
}

void postorder(nptr root)
{
    if (root == NULL)
        return;

    postorder(root->lchild);
    postorder(root->rchild);
    printf("%d ", root->data);
}

int main()
{
    printf("Enter Value of Root: ");
    int key;
    scanf("%d", &key);

    nptr root = createNode(key);

    int ch;
    
    printf("1. Insert node    2. In-Order    3. Pre-Order    4. Post-Order      5. Exit\n");

    do
    {
        printf("Command: ");
        scanf("%d", &ch);
        
        switch (ch)
        {
            case 1: char P[10];
                    printf("Enter Path: ");
                    scanf("%s", P);
                    root = insertNode(root, P);
                    break;

            case 2: inorder(root);
                    printf("\n");
                    break;

            case 3: preorder(root);
                    printf("\n");
                    break;

            case 4: postorder(root);
                    printf("\n");
                    break;
        }

    }while(ch != 5);
}