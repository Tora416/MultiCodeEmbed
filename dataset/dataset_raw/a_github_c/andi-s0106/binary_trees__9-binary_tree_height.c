#include "binary_trees.h"



size_t binary_tree_height(const binary_tree_t *tree)
{
    size_t height;

    if (tree == NULL)
    {
        return (0);
    }

    height = 0;
    height =  calc_height(tree, height);
    return (height - 1);
}


size_t calc_height(const binary_tree_t *tree, size_t height)
{
    size_t left;
    size_t right;

    left = height;
    right = height;

    if (tree == NULL)
    {
        return (0);
    }

    left = left + calc_height(tree->left, height);
    right = right + calc_height(tree->right, height);

    if (right > left)
    {
        return (right + 1);
    }
    return (left + 1);
}
