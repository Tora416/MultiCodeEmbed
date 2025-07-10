
#include<stdio.h>
#include<stdlib.h>
typedef struct x
{
    int data;
    struct x* left;
    struct x* right;
}node;
node* createNode(int n)
{
    node* newNode=(node*)malloc(sizeof(node));
    newNode->data=n;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}
node* rec_insertion(node* root, int n)
{
    if(root==NULL) return createNode(n);
    else if(n<root->data) root->left=rec_insertion(root->left,n);
    else if(n>root->data) root->right=rec_insertion(root->right,n);
    return root;
}
void iter_insertion(node** root, int n)
{
    node*** temp=&root;
    while(**temp!=NULL)
    {
        if(n < (**temp)->data) *temp=&(**temp)->left;
        else *temp=&(**temp)->right;
    }
    **temp=createNode(n);
}
void rec_inorder(node* root) 
{ 
    if (root != NULL) 
    { 
        rec_inorder(root->left); 
        printf("\t%d\n", root->data); 
        rec_inorder(root->right); 
    } 
}
void rec_preorder(node* root) 
{ 
    if (root != NULL) 
    {
        printf("\t%d\n", root->data); 
        rec_preorder(root->left);
        rec_preorder(root->right);
    }
} 
void rec_postorder(node* root) 
{ 
    if (root != NULL) 
    { 
        rec_postorder(root->left);
        rec_postorder(root->right);
        printf("\t%d\n", root->data); 
    }
} 
int main()
{
    int ch;
    node* root=NULL;
    while (1)
    {
        printf("\n1. RECURSIVE INSERTION\n");
        printf("2. ITERATIVE INSERTION\n");
        printf("3. IN-ORDER TRAVERSAL\n");
        printf("4. PRE-ORDER TRAVERSAL\n");
        printf("5. POST-ORDER TRAVERSAL\n");
        printf("6. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        if(ch==1)
        {
            int n;
            printf("Please enter an element: ");
            scanf("%d",&n);
            root=rec_insertion(root,n);
            printf("%d inserted in BINARY SEARCH TREE using Recursive Insertion\n",n);
        }
        else if(ch==2)
        {
            int n;
            printf("Please enter an element: ");
            scanf("%d",&n);
            iter_insertion(&root,n);
            printf("%d inserted in BINARY SEARCH TREE using Iterative Insertion\n",n);
        }
        else if(ch==3)
        {
            printf("\n     IN-ORDER\n");
            rec_inorder(root);
        }
        else if(ch==4)
        {
            printf("\n     PRE-ORDER\n");
            rec_preorder(root);
        }
        else if(ch==5)
        {
            printf("\n     POST-ORDER\n");
            rec_postorder(root);
        }
        else if(ch==6)
        {
            printf("Exitting Program, Thank You.\n");
            break;
        }
        else
            printf("INVALID CHOICE! TRY AGAIN\n");
    }
    return 0;
}