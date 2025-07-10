  
#include "sort.h"


int swp_fwd(listint_t *current, listint_t **list)
{
    listint_t *moving = NULL;

    moving = current->next;

    moving->prev = current->prev;
    if (current->prev)
        current->prev->next = moving;
    else
        *list = current->next;

    current->next = moving->next;
    current->prev = moving;
    moving->next = current;
    if (current->next)
        current->next->prev = current;

    print_list(*list);
    return (1);
}


int swp_bck(listint_t *current, listint_t **list)
{
    listint_t *moving = NULL;

    moving = current->prev;

    moving->next = current->next;
    current->next->prev = moving;

    current->prev = moving->prev;
    current->next = moving;
    moving->prev = current;
    if (current->prev)
        current->prev->next = current;
    else
        *list = current;
    print_list(*list);
    return (1);
}


void cocktail_sort_list(listint_t **list)
{
    listint_t *current = NULL;
    int swapped = 1;

    if (list)
    {
        current = *list;
        while (swapped)
        {
            swapped = 0;
            while (current->next)
            {
                if (current->n > current->next->n)
                {
                    swapped = swp_fwd(current, list);
                    continue;
                }
                current = current->next;
            }
            if (!swapped)
                break;
            swapped = 0;
            while (current->prev)
            {
                if (current->n < current->prev->n)
                {
                    swapped = swp_bck(current, list);
                    continue;
                }
                current = current->prev;
            }
        }
    }
}