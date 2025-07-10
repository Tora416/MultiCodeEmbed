#include<stdio.h> 
#include<stdlib.h> 
typedef struct node 
{ 
    int key; 
    struct node *left, *right; 
}list;
list *newNode(int item) 
{ 
    list *temp = (list *)malloc(sizeof(list)); 
    temp->key = item; 
    temp->left = temp->right = NULL; 
    return temp; 
} 
list* rec_insert(list* node, int key) 
{ 
    if (node == NULL) 
    return newNode(key); 
    if (key < node->key) 
        node->left = rec_insert(node->left, key); 
    else if (key > node->key) 
        node->right = rec_insert(node->right, key); 
    return node; 
}
list *insert(list* root, int n)
{
    list **temp=&root;
    while(*temp!=NULL)
    {
        if(n < (*temp)->key) temp=&(*temp)->left;
        else temp=&(*temp)->right;
    }
    *temp=newNode(n);
    return root;
}
void inorder(list *root) 
{ 
    if (root != NULL) 
    { 
        inorder(root->left); 
        printf("%d \n", root->key); 
        inorder(root->right); 
    } 
}
void preorder(list *root)
{
    if (root != NULL)
    {
        printf("%d \n", root->key); 
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(list *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d \n", root->key); 
    }
}
int main() 
{ 
    int ch;
    list* root=NULL;
    while(1)
    {
        printf("\n");
        printf("1. Insertion Using Recursive Function\n");
        printf("2. Insertion Using Iterative Function\n");
        printf("3. In-order Traversal  using a Recursive Function\n");
        printf("4. Pre-order Traversal  using a Recursive Function\n");
        printf("5. Post-order Traversal  using a Recursive Function\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        if (ch==1)
        {
            int n;
            printf("Enter the element: ");
            scanf("%d",&n);
            root=rec_insert(root,n);
            printf("%d inserted in Binary Tree\n",n);
        }
        else if(ch==2)
        {
            int n;
            printf("Enter the element: ");
            scanf("%d",&n);
            root=insert(root,n);
            printf("%d inserted in Binary Tree\n",n);
        }
        else if(ch==3)
        {
            printf("IN-ORDER\n");
            inorder(root);
        }
        else if(ch==4)
        {
            printf("PRE-ORDER\n");
            preorder(root);
        }
        else if(ch==5)
        {
            printf("POST-ORDER\n");
            postorder(root);
        }
        else if(ch==6)
        {
            printf("Thank You.\n");
            break;
        }
        else
            printf("Invalid Choice.\n");
    }
    return 0; 
}