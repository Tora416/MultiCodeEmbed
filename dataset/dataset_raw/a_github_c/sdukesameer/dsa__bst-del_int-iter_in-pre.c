
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
node* insertion(node* root, int n)
{
    if(root==NULL) return createNode(n);
    else if(n < root->data) root->left=insertion(root->left,n);
    else if(n > root->data) root->right=insertion(root->right,n);
    return root; 
}
int search(node* root, int key)
{
    if (root==NULL)
        return 0;
    else
    {
        if (key<root->data)
            search(root->left,key);
        else if(key>root->data)
            search(root->right,key);
        else
            return 1;
    }
}
node* deletion(node* root, int n)
{
    if (root==NULL) return root;
    if (n<root->data)
        root->left=deletion(root->left,n);
    else if (n>root->data)
        root->right=deletion(root->right,n);
    else
    {
        if(root->left==NULL)
        {
            node* temp=root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            node* temp=root->left;
            free(root);
            return temp;
        }
        node* temp=root->right;
        while (temp&&temp->left!=NULL)
            temp=temp->left;
        root->data=temp->data;
        root->right=deletion(root->right,temp->data);
    }
    return root;
}
void display(node* root,int n)
{
    if (root==NULL)
    {
        for (int i = 0; i < n-2; i++)
            printf(" ");
        printf("NULL\n");
    }
    else
    {
        display(root->right,n+5);
        for (int i = 0; i < n+2; i++)
            printf(" ");
        printf("/\n");
        for (int i = 0; i < n; i++)
            printf(" ");
        printf("%d\n",root->data);
        for (int i = 0; i < n+2; i++)
            printf(" ");
        printf("\\\n");
        display(root->left,n+5);
    }
}
int nodes(node* root)
{
    if(root==NULL)
        return 0;
    else
        return 1 + nodes(root->left) + nodes(root->right);
}
void inorder(node* root)
{
    node* stack[nodes(root)];
    int c=-1;
    node* cur=root;
    while(1)
    {
        while (cur)
        {
            stack[++c]=cur;
            cur=cur->left;
        }
        if (c!=-1)
        {
            printf("\t%d\n",stack[c--]->data);
            cur=stack[c+1]->right;
        }
        else
            break;
    }
}
void preorder(node* root) 
{ 
    int c=-1;
    node* stack[nodes(root)];
    stack[++c]=root;
    while(c!=-1)
    {
        printf("\t%d\n",stack[c--]->data);
        node* temp=stack[c+1];
        if(temp->right)
            stack[++c]=temp->right;
        if(temp->left)
            stack[++c]=temp->left;
    }
}
int main()
{
    int ch;
    node* root=NULL;
    while (1)
    {
        printf("\n1. INSERTION OF INTEGER\n");
        printf("2. DELETION OF INTEGER\n");
        printf("3. DISPLAY TREE\n");
        printf("4. IN-ORDER TRAVERSAL\n");
        printf("5. PRE-ORDER TRAVERSAL\n");
        printf("6. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        if(ch==1)
        {
            int n;
            printf("Please enter an element: ");
            scanf("%d",&n);
            root=insertion(root,n);
            printf("%d inserted in BINARY SEARCH TREE.\n",n);
        }
        else if(ch==2)
        {
            int n;
            printf("Please enter the element to be deleted: ");
            scanf("%d",&n);
            if(search(root,n)==1)
            {
                root=deletion(root,n);
                printf("%d deleted from BINARY SEARCH TREE.\n",n);
            }
            else
                printf("COULDN'T DELETE %d. NOT FOUND IN BS TREE.\n");
        }
        else if(ch==3)
        {
            printf("\n");
            display(root,1);
        }
        else if(ch==4)
        {
            if(root==NULL)
                printf("\tTREE EMPTY\n");
            else
            {
                printf("\n     IN-ORDER\n");
                inorder(root);
            }
        }
        else if(ch==5)
        {
            if(root==NULL)
                printf("\tTREE EMPTY\n");
            else
            {
                printf("\n     PRE-ORDER\n");
                preorder(root);
            }
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