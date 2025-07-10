#include "sort.h"

void swap_backward(listint_t *c)
{
    listint_t *tmp, *head;

    while (c->prev != NULL)
    {
        if (c->n < c->prev->n)
        {
            tmp = c->prev->prev;
            c->prev->next = c->next;
            c->next = c->prev;
            c->prev->prev = c;
            c->prev = tmp;
            c->next->next->prev = c->next;
            if (tmp != NULL)
                tmp->next = c;
            head = c;
            while (head->prev != NULL)
                head = head->prev;
            print_list(head);
        }
        else
            c = c->prev;
    }
}

void swap_forward(listint_t *c)
{
    listint_t *tmp, *head;

    tmp = c->prev;

    if (tmp != NULL)
    {
        tmp->next = c->next;
        c->next->prev = tmp;
    }
    else
        c->next->prev = NULL;
    c->prev = c->next;
    if (c->next->next != NULL)
    {
        c->next = c->next->next;
        c->prev->next = c;
        c->next->prev = c;
    }
    else
    {
        c->next->next = c;
        c->next = NULL;
    }
    head = c;
    while (head->prev != NULL)
        head = head->prev;
    print_list(head);
    swap_backward(c->prev);
}

void insertion_sort_list(listint_t **list)
{
    listint_t *c;

    if ((list == NULL) || (*list == NULL) || ((*list)->next == NULL))
        return;
    c = *list;

    while (c->next != NULL)
    {
        if (c->n > c->next->n)
        {
            swap_forward(c);
        }
        else
            c = c->next;
    }
    while ((*list)->prev != NULL)
        *list = (*list)->prev;
}
