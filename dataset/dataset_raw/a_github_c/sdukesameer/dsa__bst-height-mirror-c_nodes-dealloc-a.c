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
        printf("   %d \n", root->key); 
        inorder(root->right); 
    } 
}
void preorder(list *root)
{
    if (root != NULL)
    {
        printf("   %d \n", root->key); 
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
        printf("   %d \n", root->key); 
    }
}
int rec_height(list* node)
{
    if(node==NULL)
    return 0;
    else
    {
    int lheight=rec_height(node->left);
    int rheight=rec_height(node->right);
    if(lheight> rheight)
        return (lheight+1);
    else return (rheight+1);
    }
}
void mirror_ins(list* node)
{
    if(node==NULL)
    return ;
    else
    {
        list* temp;
        mirror_ins(node->left);
        mirror_ins(node->right);
        temp=node->left;
        node->left=node->right;
        node->right=temp;
    }
}
int rec_count(list* node)
{
    int x=1;
    if(node==NULL)
        return 0;
    else
    {
        x+=rec_count(node->left);
        x+=rec_count(node->right);
        return x;
    }
}
int leafcount(list* node)
{
    if(node==NULL)
        return 0;
    if(node->left==NULL && node->right==NULL)
        return 1;
    else
        return leafcount(node->left)+leafcount(node->right);
}
int InternalNodeCount(list* node)
{
    if(node==NULL ||(node->left==NULL && node->right==NULL))
        return 0;
    else
        return 1 + InternalNodeCount(node->left)+InternalNodeCount(node->right);
}
int findmax(list* node)
{
    if(node==NULL || node->right==NULL)
        return node->key;
    else
        findmax(node->right);
}
int findmin(list* node)
{
    if(node==NULL || node->left==NULL)
        return node->key;
    else
        findmin(node->left);
}
void deleteTree(list* node)
{
    if(node == NULL)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    printf("\n Deleting Node: %d",node->key);
    free(node);
}
int main() 
{ 
    int ch;
    list* root=NULL;
    while(1)
    {
        printf("\n");
        printf("1. Insertion Using Recursive Function \n");
        printf("2. Insertion Using Iterative Function \n");
        printf("3. In-order Traversal  using a Recursive Function \n");
        printf("4. Pre-order Traversal  using a Recursive Function \n");
        printf("5. Post-order Traversal  using a Recursive Function \n");
        printf("6. Determine the height of the Binary Search Tree \n");
        printf("7. Construct the Binary Search Tree which is mirror image of the given Binary Search Tree \n");
        printf("8. Count the total number of nodes of the Binary Search Tree \n");
        printf("9. Count the total number of leaf nodes of the Binary Search Tree \n");
        printf("10. Count the total number of internal nodes of the Binary Search Tree \n");
        printf("11. Find maximum and minimum elements in the Binary Search Tree \n");
        printf("12. Deallocate the memory space occupied by Binary Search Tree \n");
        printf("13. Exit Program \n");
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
            printf("\nIN-ORDER\n");
            inorder(root);
        }
        else if(ch==4)
        {
            printf("\nPRE-ORDER\n");
            preorder(root);
        }
        else if(ch==5)
        {
            printf("\nPOST-ORDER\n");
            postorder(root);
        }
        else if (ch==6)
        {
            printf("Height of tree= %d\n",rec_height(root));
        }
        else if (ch==7)
        {
            mirror_ins(root);
            printf("Mirror of tree constructed\n");
        }
        else if (ch==8)
        {
            printf("Total number of nodes= %d\n",rec_count(root));
        }
        else if (ch==9)   
        {
            printf("Number of leaf nodes= %d\n",leafcount(root));
        }
        else if (ch==10)
        {
            printf("Number of internal nodes= %d\n",InternalNodeCount(root));
        }
        else if (ch==11)
        {
            printf("Maximum= %d\n",findmax(root));
            printf("Minimum= %d\n",findmin(root));
        }
        else if (ch==12)
        {
            deleteTree(root);
            root=NULL;
        }
        else if (ch==13)
        {
            printf("Thank You.\n");
            break;
        }
        else
            printf("Invalid Choice.\n");
    }
    return 0; 
}