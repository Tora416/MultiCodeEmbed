#include "binary_trees.h"


size_t count_leaves(const binary_tree_t *tree)
{
    int count = 0;

    if (tree == NULL)
    {
        return (0);
    }
    if ((*tree).right == NULL && (*tree).left == NULL)
    {
        return (1);
    }
    count = count_leaves((*tree).right) + count_leaves((*tree).left);
    return (count);
}


size_t internal_nodes(const binary_tree_t *tree)
{
    int c = 0;

    if (tree == NULL)
    {
        return (0);
    }
    if ((*tree).right != NULL || (*tree).left != NULL)
    {
        c = 1 + internal_nodes((*tree).right) + internal_nodes((*tree).left);
    }
    return (c);
}


size_t tree_size(const binary_tree_t *tree)
{
    int count = 0;

    if (tree == NULL)
    {
        return (0);
    }
    count = 1 + tree_size((*tree).left) + tree_size((*tree).right);
    return (count);
}


int binary_tree_is_full(const binary_tree_t *tree)
{
    int _inodes = 0, _nodes = 0, _leaves = 0;

    if (tree == NULL)
    {
        return (0);
    }
    _nodes = tree_size(tree);
    _leaves = count_leaves(tree);
    _inodes = internal_nodes(tree);
    if (_inodes > 0)
    {
        if (_leaves != _inodes + 1)
        {
            return (0);
        }
        if (_nodes != 2 * _inodes + 1)
        {
            return (0);
        }
    }
    if (_inodes != (_nodes - 1) / 2)
    {

        return (0);
    }
    if (_leaves != (_nodes + 1) / 2)
    {
        return (0);
    }
    if (_nodes != 2 * _leaves - 1)
    {

        return (0);
    }
    if (_inodes != _leaves - 1)
    {
        return (0);
    }
    return (1);
}
