#include "binary_trees.h"


binary_tree_t *brother(binary_tree_t *node)
{
    binary_tree_t *parent = NULL;

    if (node == NULL)
    {
        return (NULL);
    }
    if ((*node).parent == NULL)
    {
        return (NULL);
    }
    parent = (*node).parent;
    if ((*parent).left != NULL && (*parent).right != NULL)
    {
        if (node == (*parent).left)
            return ((*parent).right);
        return ((*parent).left);
    }
    return (NULL);
}


binary_tree_t *binary_tree_uncle(binary_tree_t *node)
{

    if (node == NULL)
    {
        return (NULL);
    }
    if ((*node).parent == NULL)
    {
        return (NULL);
    }
    return (brother((*node).parent));
}
