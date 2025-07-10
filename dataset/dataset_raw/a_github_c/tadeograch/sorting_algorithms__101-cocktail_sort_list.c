#include "sort.h"



void cocktail_sort_list(listint_t **list)
{
    listint_t *recorro, *temp;

    if (!list || *list == NULL)
        return;

    if ((*list)->next == NULL)
        return;

    temp = (*list)->next;
    while (temp != NULL)
    {
        recorro = *list;
        while (recorro->next != NULL)
        {
            if (recorro->n > recorro->next->n)
            {
                swap(recorro->next, recorro, list);
                print_list(*list);
            }
            else
                recorro = recorro->next;
        }
        while (recorro->prev != NULL)
        {
            if (recorro->n < recorro->prev->n)
            {
                swap(recorro, recorro->prev, list);
                print_list(*list);
            }
            else
                recorro = recorro->prev;
        }
        temp = temp->next;
    }
}


listint_t **swap(listint_t *temp_sort, listint_t *swapper, listint_t **list)
{
    listint_t *aux_prev, *aux_next = temp_sort->next;

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
