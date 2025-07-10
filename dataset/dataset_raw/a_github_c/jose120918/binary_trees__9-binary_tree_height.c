#include "binary_trees.h"


int scale(const binary_tree_t *tree)
{
    int ll = 1;
    int lr = 1;

    if (tree == NULL)
    {
        return (-1);
    }
    ll += scale((*tree).left);
    lr += scale((*tree).right);
    if (lr > ll)
    {
        return (lr);
    }
    return (ll);
}


size_t binary_tree_height(const binary_tree_t *tree)
{
    if (tree == NULL)
    {
        return (0);
    }
    return (scale(tree));
}
