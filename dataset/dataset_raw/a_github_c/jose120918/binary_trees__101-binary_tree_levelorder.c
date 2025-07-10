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


void print_level(binary_tree_t *tree, int level, void (*func)(int))
{
    if (tree != NULL)
    {
        if (level == 0)
        {
            func((*tree).n);
        }
        else
        {
            print_level((*tree).left, level - 1, func);
            print_level((*tree).right, level - 1, func);
        }
    }
}


void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
    int level, height;

    if (tree != NULL && func != NULL)
    {
        height = scale(tree) + 1;

        for (level = 0; level < height; level++)
        {
            print_level((binary_tree_t *)tree, level, func);
        }
    }
}
