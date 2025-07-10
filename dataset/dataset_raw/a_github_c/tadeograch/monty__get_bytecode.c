#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "monty.h"

int get_bytecode(char *filename)
{
    FILE *fp;
    char *line = NULL;
    unsigned int line_number = 0;
    size_t len = 0;
    ssize_t read;
    stack_t *stack = NULL;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: Can't open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    while ((read = getline(&line, &len, fp)) != -1)
    {
        line_number++;
        split_buffer(line);
        if (code[0] == NULL)
            continue;
        if (strcmp(code[0], "push") == 0 && check_number(code[1]) == 1)
        {
            printf("L%d: usage: push integer\n", (line_number));
            free(line);
            free_dlistint(stack);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        if (analize(&stack, line_number) == 0)
        {
            printf("L%d: unknown instruction %s\n", line_number, code[0]);
            free_dlistint(stack);
            free(line);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }
    free(line);
    free_dlistint(stack);
    fclose(fp);
    return (0);
}
