#include "binary_trees.h"



size_t binary_tree_nodes(const binary_tree_t *tree)
{
    size_t nodes;

    if (tree == NULL)
    {
        return (0);
    }

    nodes = 0;
    nodes = count_nodes(tree, nodes);

    return (nodes);
}



size_t count_nodes(const binary_tree_t *tree, size_t nodes)
{
    size_t left;
    size_t right;

    left = nodes;
    right = nodes;

    if (tree == NULL)
    {
        return (0);
    }

    if (tree->right != NULL || tree->right != NULL)
    {
        nodes = nodes + 1;
    }

    left = left + count_nodes(tree->left, left);
    right = right + count_nodes(tree->right, right);

    return (nodes + left + right);
}
