#include "monty.h"
#include <stdlib.h>
#include <stdio.h>


void push_func(stack_t **stack, unsigned int line_number)
{
    int n;
    stack_t *new = malloc(sizeof(stack_t));
    (void)line_number;

    if (!new)
    {
        free(new);
        return;
    }
    n = atoi(code[1]);
    new->n = n;
    new->prev = NULL;
    if (!*stack)
    {
        new->next = NULL;
        *stack = new;
    }
    else
    {
        new->next = *stack;
        (*stack)->prev = new;
        *stack = new;
    }
}
