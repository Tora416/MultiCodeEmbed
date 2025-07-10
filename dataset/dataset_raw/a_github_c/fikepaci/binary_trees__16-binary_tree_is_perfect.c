#include "binary_trees.h"

unsigned char is_leaf(const binary_tree_t *node);
size_t depth(const binary_tree_t *tree);
const binary_tree_t *get_leaf(const binary_tree_t *tree);
int is_perfect_recursive(const binary_tree_t *tree,
        size_t leaf_depth, size_t level);
int binary_tree_is_perfect(const binary_tree_t *tree);


unsigned char is_leaf(const binary_tree_t *node)
{
    return ((node->left == NULL && node->right == NULL) ? 1 : 0);
}


size_t depth(const binary_tree_t *tree)
{
    return (tree->parent != NULL ? 1 + depth(tree->parent) : 0);
}


const binary_tree_t *get_leaf(const binary_tree_t *tree)
{
    if (is_leaf(tree) == 1)
        return (tree);
    return (tree->left ? get_leaf(tree->left) : get_leaf(tree->right));
}


int is_perfect_recursive(const binary_tree_t *tree,
        size_t leaf_depth, size_t level)
{
    if (is_leaf(tree))
        return (level == leaf_depth ? 1 : 0);
    if (tree->left == NULL || tree->right == NULL)
        return (0);
    return (is_perfect_recursive(tree->left, leaf_depth, level + 1) &&
            is_perfect_recursive(tree->right, leaf_depth, level + 1));
}


int binary_tree_is_perfect(const binary_tree_t *tree)
{
    if (tree == NULL)
        return (0);
    return (is_perfect_recursive(tree, depth(get_leaf(tree)), 0));
}
