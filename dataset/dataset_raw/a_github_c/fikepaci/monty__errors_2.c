#include "monty.h"

int short_stack_error(unsigned int line_number, char *op);
int div_error(unsigned int line_number);
int pop_error(unsigned int line_number);
int div_error(unsigned int line_number);
int pchar_error(unsigned int line_number, char *message);


int pop_error(unsigned int line_number)
{
    fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
    return (EXIT_FAILURE);
}


int pint_error(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
    return (EXIT_FAILURE);
}


int short_stack_error(unsigned int line_number, char *op)
{
    fprintf(stderr, "L%u: can't %s, stack too short\n", line_number, op);
    return (EXIT_FAILURE);
}


int div_error(unsigned int line_number)
{
    fprintf(stderr, "L%u: division by zero\n", line_number);
    return (EXIT_FAILURE);
}


int pchar_error(unsigned int line_number, char *message)
{
    fprintf(stderr, "L%u: can't pchar, %s\n", line_number, message);
    return (EXIT_FAILURE);
}
