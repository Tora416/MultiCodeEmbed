#include "binary_trees.h"

size_t binary_tree_height(const binary_tree_t *tree)
{
    size_t height_left = 0;
    size_t height_right = 0;

    if (tree == NULL)
        return (-1);
    if (tree->left == NULL && tree->right == NULL)
        return (0);
    height_left = binary_tree_height(tree->left) + 1;
    height_right = binary_tree_height(tree->right) + 1;
    if (height_left > height_right)
        return (height_left);
    return (height_right);
}


int binary_tree_balance(const binary_tree_t *tree)
{
    size_t height_left = 0;
    size_t height_right = 0;

    if (tree == NULL)
        return (0);
    height_left = binary_tree_height(tree->left);
    height_right = binary_tree_height(tree->right);
    return (height_left - height_right);
}


int binary_tree_is_perfect(const binary_tree_t *tree)
{
    if (tree == NULL || (binary_tree_balance(tree) != 0))
        return (0);
    if (tree->left == NULL && tree->right == NULL)
        return (1);
    return (binary_tree_is_perfect(tree->left)
        * binary_tree_is_perfect(tree->right));
}
