#include<stdio.h>
#include<stdlib.h>
struct tree
{
    int val;
    struct tree *left;
    struct tree *right;
}*root=NULL,*temp=NULL,*q=NULL;
int value;
struct tree* find_max(struct tree* root)
{
    if(root==NULL || root->right==NULL)
    return(root);
    else
    return(find_max(root->right));  
}
struct tree* insert(struct tree* root,int tar)
{
    struct tree* p=(struct tree*)malloc(sizeof(struct tree));
    p->val=tar;
    p->left=NULL;
    p->right=NULL;
    if(root!=NULL)
    {
        if(tar<root->val)
        root->left=insert(root->left,tar);
        else if(tar>root->val)
        root->right=insert(root->right,tar);
        else if(tar==root->val)
        return(root);
    }
    else
    {
        root=p;
        return(root);
    }
}
struct tree* delete(struct tree* root,int tar)
{
    if(root!=NULL)
    {
        if(tar<root->val)
        root->left=delete(root->left,tar);
        else if(tar>root->val)
        root->right=delete(root->right,tar);
        else if(tar==root->val)
        {
            if(root->left==NULL && root->right==NULL)
            {
                root=NULL;
            }
            else if(root->left==NULL && root->right!=NULL)
            {
                temp=root;
                root=root->right;
                free(temp);
            }
            else if(root->left!=NULL && root->right==NULL)
            {
                temp=root;
                root=root->left;
                free(temp);
            }
            else
            {
                temp=find_max(root->left);
                root->val=temp->val;
                root->left=delete(root->left,temp->val);
            }
        }
        return(root);
    }
    else
    {
        return(root);
    }
}
struct tree* search(struct tree* root,int tar)
{
    if(root!=NULL)
    {
        if(tar<root->val)
        root->left=search(root->left,tar);
        else if(tar>root->val)
        root->right=search(root->right,tar);
        else if(tar==root->val)
        {
            printf("\nElement found");
            return(root);
        }       
    }
    else
    {
        printf("\neither tree is empty or element not found");
        return(root);
    }
}
void inorder(struct tree* root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        printf("\t%d",root->val);
        inorder(root->right);
    }
}
void preorder(struct tree* root)
{
    if(root!=NULL)
    {
        printf("\t%d",root->val);
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(struct tree* root)
{
    if(root!=NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("\t%d",root->val);
    }
}
void main()
{
    int ch;
    while(1)
    {
        printf("\nEnter choice:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            {
                printf("\nEnter value to insert:");
                scanf("%d",&value);
                root=insert(root,value);
                break;
            }
            case 2:
            {
                printf("\nEnter the value to delete:");
                scanf("%d",&value);
                root=delete(root,value);
                break;
            }
            case 3:
            {
                printf("\nEnter the value to search:");
                scanf("%d",&value);
                root=search(root,value);
                break;
            }
            case 4:
            {
                inorder(root);
                break;
            }
            case 5:
            {
                preorder(root);
                break;
            }
            case 6:
            {
                postorder(root);
                break;
            }
            default:
            {
                exit(0);
                break;
            }
        }
    }
}