#include "monty.h"
#include <string.h>

void free_stack(stack_t **stack);
int init_stack(stack_t **stack);
int check_mode(stack_t *stack);


void free_stack(stack_t **stack)
{
    stack_t *tmp = *stack;

    while (*stack)
    {
        tmp = (*stack)->next;
        free(*stack);
        *stack = tmp;
    }
}


int init_stack(stack_t **stack)
{
    stack_t *s;

    s = malloc(sizeof(stack_t));
    if (s == NULL)
        return (malloc_error());

    s->n = STACK;
    s->prev = NULL;
    s->next = NULL;

    *stack = s;

    return (EXIT_SUCCESS);
}

