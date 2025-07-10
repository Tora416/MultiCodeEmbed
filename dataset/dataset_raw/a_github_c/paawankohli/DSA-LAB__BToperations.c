nptr copy(nptr original)
{
    if (original == NULL)
        return NULL;

    temp = createNode(original -> data);
    temp -> lchild = copy(original -> lchild);
    temp -> rchild = copy(original -> rchild);
    return temp;
}

int searchBT(nptr root, int x)
{
    if(root == NULL)
        return 0;

    else if (root -> data  == x  ||  searchBT(root -> lchild, x)  ||   searchBT(root -> rchild, x) )
        return 1;
}

int height(nptr root)
{
    if (root == NULL)
        return 0;
    
    return max(height(root->right), height(root->left)) + 1;
}

int Equal( Nodeptr root1, Nodeptr root2)
{
    return  ((root1 == NULL && root2 == NULL) || (root1 && root2 && root1 -> data == root2 -> data)) 
            && Equal(root1->lchild, root2->lchild) 
            && Equal(root1->rchild, root2->rchild);
}

void getlevel(node* r, int level)
{
    if (level == 0)
        printf("%d\t", r -> data);
    
    else
    {
        getlevel(r->left, level-1);
        getlevel(r->right, level-1);
    } 
}

