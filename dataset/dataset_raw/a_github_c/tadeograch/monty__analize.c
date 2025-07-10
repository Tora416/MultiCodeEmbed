#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"


int analize(stack_t **stack, unsigned int line_number)
{
    int type_i;
    instruction_t type[] = {
                {"push", push_func},
                {"pall", pall_func},
                {"pint", pint_func},
                {"pop", pop_func},
                {"swap", swap_func},
                {"add", add_func},
                {"nop", nop_func},
                {"sub", sub_func},
                {"div", div_func},
                {"mul", mul_func},
                {"mod", mod_func},
                {NULL, NULL}
    };

    for (type_i = 0; type[type_i].opcode != NULL; type_i++)
    {
        if (strcmp(code[0], type[type_i].opcode) == 0)
        {
            type[type_i].f(stack, line_number);
            break;
        }
    }
    if (type[type_i].opcode == NULL)
    {
        return (0);
    }
    return (1);
}
