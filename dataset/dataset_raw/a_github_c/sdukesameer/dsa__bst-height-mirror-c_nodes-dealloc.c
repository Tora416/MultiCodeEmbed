
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
int height(node* root)
{
    if(root==NULL)
        return 0;
    else
    {
        int lheight=height(root->left);
        int rheight=height(root->right);
        if(lheight>rheight)
            return lheight+1;
        else
            return rheight+1;
    }
}
void mirror_image(node** root)
{
    node* temp;
    if((*root)!=NULL)
    {
        mirror_image(&(*root)->left);
        mirror_image(&(*root)->right);
        temp=(*root)->left;
        (*root)->left=(*root)->right;
        (*root)->right=temp;
    }
}
int count_totalnodes(node* root)
{
    if(root==NULL)
        return 0;
    else
        return 1 + count_totalnodes(root->left) + count_totalnodes(root->right);
}
int count_leafnodes(node* root)
{
    if (root==NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    else
        return count_leafnodes(root->left) + count_leafnodes(root->right);
}
int count_internalnodes(node* root)
{
    if(root == NULL || (root->left == NULL && root->right == NULL))
        return 0;
    else
        return 1 + count_internalnodes(root->left)+count_internalnodes(root->right);
}
int largest_element(node* root)
{
    if(root==NULL||root->right==NULL)
        return root->data;
    else
        largest_element(root->right);
}
int smallest_element(node* root)
{
    if(root==NULL||root->left==NULL)
        return root->data;
    else
        smallest_element(root->left);
}
void deallocate_space(node* root)
{
    if((root)!=NULL)
    {
        deallocate_space(root->left);
        deallocate_space(root->right);
        printf("\nDeallocating space occupied by element: %d",root->data);
        free(root);
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
        printf("6. HEIGHT OF BINARY TREE\n");
        printf("7. CONSTRUCT MIRROR IMAGE\n");
        printf("8. COUNT TOTAL NUMBER OF NODES\n");
        printf("9. COUNT TOTAL NUMBER OF LEAF NODES\n");
        printf("10. COUNT TOTAL NUMBER OF INTERNAL NODES\n");
        printf("11. MAX AND MIN ELEMENTS IN THE BINARY TREE\n");
        printf("12. DEALLOCATE SPACE OCCUPIED BY BINARY TREE\n");
        printf("13. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        if(ch==1)
        {
            int n;
            printf("Please enter an element: ");
            scanf("%d",&n);
            root=rec_insertion(root,n);
            printf("\n%d inserted in BINARY SEARCH TREE using Recursive Insertion\n",n);
        }
        else if(ch==2)
        {
            int n;
            printf("Please enter an element: ");
            scanf("%d",&n);
            iter_insertion(&root,n);
            printf("\n%d inserted in BINARY SEARCH TREE using Iterative Insertion\n",n);
        }
        else if(ch==3)
        {
            if(root==NULL)
                printf("\n\tTREE EMPTY\n");
            else
            {
                printf("\n     IN-ORDER\n");
                rec_inorder(root);
            }
        }
        else if(ch==4)
        {
            if(root==NULL)
                printf("\n\tTREE EMPTY\n");
            else
            {
                printf("\n     PRE-ORDER\n");
                rec_preorder(root);
            }
        }
        else if(ch==5)  
        {
            if(root==NULL)
                printf("\n\tTREE EMPTY\n");
            else
            {
                printf("\n     POST-ORDER\n");
                rec_postorder(root);
            }
        }
        else if(ch==6)
            printf("\nHeight of the tree: %d\n",height(root));
        else if(ch==7)
        {
            mirror_image(&root);
            printf("\nImage Tree Created\n");
        }
        else if(ch==8)
                printf("\nTotal number of nodes: %d\n",count_totalnodes(root));
        else if(ch==9)
            printf("\nNumber of leaf nodes: %d\n",count_leafnodes(root));
        else if(ch==10)
            printf("\nNumber of internal nodes: %d\n",count_internalnodes(root));
        else if(ch==11)
        {
            printf("\nMaximum element: %d\n",largest_element(root));
            printf("Minimum element: %d\n",smallest_element(root));
        }
        else if(ch==12)
        {
            deallocate_space(root);
            root=NULL;
            printf("\n\nDeallocated the space occupied by Binary Tree.\n");
        }
        else if(ch==13)
        {
            
            printf("\nExitting Program, Thank You.\n");
            break;
        }
        else
            printf("\nINVALID CHOICE! TRY AGAIN\n");
    }
    return 0;
}