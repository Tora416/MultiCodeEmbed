#include "binary_trees.h"


binary_tree_t *binary_tree_rotate_right(binary_tree_t *tree)
{
    binary_tree_t *y, *x;

    if (tree != NULL)
    {
        x = tree;
        if ((*x).left != NULL)
        {
            y = (*x).left;
            
            (*x).left = (*y).right;
            if ((*y).right != NULL)
            {
                (*(*y).right).parent = x;
            }
            
            (*y).parent = (*x).parent;
            if ((*x).parent == NULL)
            {
                tree = y;
            }
            else if (x == (*(*x).parent).right)
            {
                (*(*x).parent).right = y;
            }
            else
            {
                (*(*x).parent).left = y;
            }
            
            (*y).right = x;
            (*x).parent = y;
            return (tree);
        }
    }
    return (NULL);
}
