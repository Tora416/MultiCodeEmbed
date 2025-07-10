#include <stdio.h>
#include <stdlib.h>
#include "monty.h"


unsigned int print_dlistint(const stack_t *h)
{
    unsigned int n = 0;

    while (h)
    {
        printf("%i\n", h->n);
        n++;
        h = h->next;
    }
    return (n);
}


unsigned int _strlen(char *s)
{
    unsigned int n, len;

    n = len = 0;
    while (*(s + n) != '\0')
    {
        n++;
        len++;
    }
    return (len);
}


unsigned int dlistint_len(const stack_t *h)
{
    unsigned int n = 0;

    if (h == NULL)
    {
        return (0);
    }
    while (h != NULL)
    {
        n++;
        h = h->next;
    }
    return (n);
}


void free_dlistint(stack_t *head)
{
    stack_t *aux;

    while (head != NULL)
    {
        aux = head;
        head = head->next;
        free(aux);
    }
}
