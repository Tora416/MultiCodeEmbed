#include "sort.h"

void swap_func(listint_t **list, listint_t *node)
{
    listint_t *tmp;

    tmp = node->next;
    if (tmp->next)
        tmp->next->prev = node;
    tmp->prev = node->prev;
    node->next = tmp->next;
    tmp->next = node;
    if (node->prev)
        node->prev->next = tmp;
    node->prev = tmp;
    if (*list == node)
        *list = tmp;
}


void cocktail_sort_list(listint_t **list)
{
    listint_t *current;
    int flag = 1;

    if (list == NULL || *list == NULL || (*list)->next == NULL)
        return;
    current = *list;
    while (flag > 0)
    {
        flag = 0;
        while (current->next != NULL)
        {
            if (current->n > current->next->n)
            {
                swap_func(list, current);
                print_list(*list);
                flag = 1;
            }
            else
                current = current->next;
        }
        if (flag == 0)
            break;
        flag = 0;
        while (current->prev != NULL)
        {
            if (current->n < current->prev->n)
            {
                swap_func(list, current->prev);
                print_list(*list);
                flag = 1;
            }
            else
                current = current->prev;
        }
    }
}
