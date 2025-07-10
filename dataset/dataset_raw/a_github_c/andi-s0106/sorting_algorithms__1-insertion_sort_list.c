#include "sort.h"
listint_t *swap(listint_t **current, listint_t **sorted);

void insertion_sort_list(listint_t **list)
{
    listint_t *current;
    listint_t *sorted;


    if (list == NULL || *list == NULL || (*list)->next == NULL)
        return;

    sorted = *list;
    current = (*list)->next;

    while (current != NULL)
    {
        if (sorted != NULL &&  current->n < sorted->n)
        {

            current = swap(&current, &sorted);
            sorted = current->prev;
            if (sorted == NULL)
                *list = current;
            print_list(*list);

            while (sorted != NULL && current->n < sorted->n)
            {
                current = swap(&current, &sorted);
                sorted = current->prev;
                if (sorted == NULL)
                    *list = current;
                print_list(*list);
            }
        }
        else
        {
            sorted = current;
            current = sorted->next;
        }
    }
}


listint_t *swap(listint_t **current, listint_t **sorted)
{
    listint_t *tmp;

    tmp = (*current)->next;
    if (*sorted != NULL)
        (*sorted)->next = tmp;
    if (tmp != NULL)
    {
        tmp->prev = *sorted;
    }
    if (*current != NULL)
        (*current)->next = *sorted;
        (*current)->prev = (*sorted)->prev;
    if ((*sorted)->prev != NULL)
        (*sorted)->prev->next = *current;
    ((*sorted)->prev) = *current;

    return (*current);
}
