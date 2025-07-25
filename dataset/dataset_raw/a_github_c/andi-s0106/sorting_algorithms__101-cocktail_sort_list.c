#include "sort.h"
int swap(listint_t **list, listint_t *current, int);


void cocktail_sort_list(listint_t **list)
{
    int flag;
    listint_t *tmp;

    flag = 0;
    if (list == NULL || *list == NULL || (*list)->next == NULL)
        return;
    tmp = *list;
    while (flag == 0)
    {
        flag = 1;
        while (tmp->next != NULL)
        {
            if (tmp->n > tmp->next->n)
                flag = swap(list, tmp, 0);
            else
                tmp = tmp->next;
        }
        tmp = tmp->prev;
        if (flag == 1)
            break;
        while (tmp->prev != NULL)
        {
            if (tmp->n < tmp->prev->n)
                flag = swap(list, tmp, 1);
            else
                tmp = tmp->prev;
        }
        if (flag == 1)
            break;
    }
}


int swap(listint_t **list, listint_t *current, int flag)
{
    listint_t *tmp;

    if (list == NULL || *list == NULL || current == NULL)
        return (1);

    if (flag == 1)
        current = current->prev;
    tmp = current->next;

    if (tmp != NULL)
    {
        current->next = tmp->next;
        tmp->next = current;
        tmp->prev = current->prev;
    }
    if (current->next != NULL)
        current->next->prev = current;
    if (current->prev != NULL)
        current->prev->next = tmp;
    current->prev = tmp;

    if (tmp->prev == NULL)
        *list = tmp;

    print_list(*list);
    return (0);
}
