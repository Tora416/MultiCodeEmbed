#include <stdio.h>
#include<stdlib.h>
#include<string.h>
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};
struct Node* BSTInsert(struct Node** root,int data)
{
    if(!*root)
    {
        struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
        newNode->data=data;
        newNode->left=NULL;
        newNode->right=NULL;
        return newNode;
    }
    else
    {
        if((*root)->data>data)
        {
            (*root)->left=BSTInsert(&((*root)->left),data);
        }
        else if((*root)->data<data)
        {
            (*root)->right=BSTInsert(&((*root)->right),data);
        }
        else
        {
            printf("The element already exists in the BST\n");
        }
    }
    return *root;
    
}
void inorder(struct Node* root)
{
    if(!root)
        return;
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
    return;
}
void preorder(struct Node* root)
{
    if(!root)
        return;
    printf("%d ",root->data);
    preorder(root->left);
    preorder(root->right);
    return;
}
void postorder(struct Node* root)
{
    if(!root)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->data);
    return;
}
int main()
{
    int n;
    int k;
    struct Node* root=NULL;
    printf("Please enter the number of nodes you want to insert\n");
    scanf("%d",&n);
    printf("Please enter the elements\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&k);
        root=BSTInsert(&root,k);
    }
    inorder(root);
    printf("\n");
    preorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    return 0;
}