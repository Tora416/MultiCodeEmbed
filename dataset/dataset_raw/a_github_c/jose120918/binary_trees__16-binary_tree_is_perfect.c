#include "binary_trees.h"


int _pow(int x, int y)
{
    if (y < 0)
        return (-1);
    if (y == 0)
        return (1);
    if (y > 1)
    {
        y = _pow(x, y - 1);
    }
    else
    {
        return (x * y);
    }
    return (x * y);
}


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


int binary_tree_is_perfect(const binary_tree_t *tree)
{
    int height;
    int _nodes;

    if (tree == NULL)
        return (0);

    height = scale(tree);
    _nodes = tree_size(tree);
    if (_pow(2, height + 1) - 1 == _nodes)
        return (1);
    return (0);
}
