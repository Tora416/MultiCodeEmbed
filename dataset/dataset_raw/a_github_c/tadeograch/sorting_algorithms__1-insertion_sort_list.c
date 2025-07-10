#include "sort.h"


void insertion_sort_list(listint_t **list)
{
    listint_t *temp_n, *temp_sort, *swapper;

    if (!list || *list == NULL)
        return;

    if ((*list)->next == NULL)
        return;

    temp_n = *list;

    while (temp_n != NULL)
    {
        temp_sort = temp_n;
        if (temp_sort->prev != NULL)
        {
            while (temp_sort->n < (temp_sort->prev)->n && temp_sort->prev != NULL)
            {
                swapper = temp_sort->prev;
                if (swapper->prev == NULL)
                {
                    swap(temp_sort, swapper, list);
                    print_list(*list);
                    break;
                }
                swap(temp_sort, swapper, list);
                print_list(*list);
            }
        }
        temp_n = temp_n->next;
    }
}


listint_t **swap(listint_t *temp_sort, listint_t *swapper, listint_t **list)
{
    listint_t *aux_prev, *aux_next = temp_sort->next;

    swapper = temp_sort->prev;
    if (temp_sort->next == NULL && swapper->prev == NULL)
    {
        temp_sort->next = temp_sort->prev;
        temp_sort->prev = NULL;
        swapper->prev = swapper->next;
        swapper->next = NULL;
        *list = temp_sort;
    }
    else if (swapper->prev == NULL)
    {
        temp_sort->prev = NULL;
        temp_sort->next = swapper;
        swapper->prev = temp_sort;
        swapper->next = aux_next;
        aux_next->prev = swapper;
        *list = temp_sort;
    }
    else if (temp_sort->next == NULL)
    {
        aux_prev = swapper->prev;
        aux_prev->next = temp_sort;
        temp_sort->prev = aux_prev;
        temp_sort->next = swapper;
        swapper->prev = temp_sort;
        swapper->next = NULL;
    }
    else
    {
        aux_prev = swapper->prev;
        aux_prev->next = temp_sort;
        temp_sort->prev = aux_prev;
        temp_sort->next = swapper;
        swapper->next = aux_next;
        swapper->prev = temp_sort;
        aux_next->prev = swapper;
    }
    return (list);
}
