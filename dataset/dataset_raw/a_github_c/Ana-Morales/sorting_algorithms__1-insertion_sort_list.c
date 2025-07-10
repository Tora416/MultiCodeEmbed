#include "sort.h"


void insertion_sort_list(listint_t **list)
{

    listint_t *p, *c, *aux;

    if (list == NULL || *list == NULL || (*list)->next == NULL)
        return;
    c = (*list)->next;
    aux = (*list)->next;
    while (aux != NULL)
    {
        aux = aux->next;
        while (c->prev != NULL)
        {
            if (c->prev->n > c->n)
            {
                p = c->prev;
                p->next = c->next;
                if (c->next)
                    c->next->prev = p;
                c->next = p;
                c->prev = p->prev;
                if (p->prev)
                    p->prev->next = c;
                p->prev = c;
                if (p == *list)
                    *list = c;
                print_list(*list);
            }
            else
                break;
        }
        c = aux;
    }
}
