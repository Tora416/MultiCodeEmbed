











int     operation(int a, int b, char op)
{
    if (op == '+')
        return (a + b);
    if (op == '-')
        return (a - b);
    if (op == '*')
        return (a * b);
    if (op == '/')
    {
        if (b == 0)
            return (99);
        return (a / b);
    }
    if (op == '%')
    {
        if (b == 0)
            return (99);
        return (a % b);
    }
    return (99);
}

int     isop(char   op)
{
    if (op == '+' || op == '-' || op == '/' || op == '%' || op == '*')
        return (1);
    return(0);
}

int     isnum(char *str)
{
    int ctrl;
    ctrl = 0;
    if (str[ctrl] == '+' || str[ctrl] == '-')
        ctrl++;
    if (str[ctrl] >= 0 && str[ctrl] <= 9)
        return (1);
    return (0);
}

int     rpn_calc(char *str, int *stack)
{
    int     ctrl;
    int     top;

    top = -1;
    ctrl = 0;
    while(str[ctrl])
    {
        if(isnum(str))
        {
            top++;
            stack[top] = atoi(&str[ctrl]);
            while (str[ctr] != ' ' && str[ctrl] != '\0')
                ctrl++;
        }
        if (isop(str[ctrl]))
        {
            if (top > 0)
            {
                if(stack[top - 1] = operate(stack[top - 1],stack[top],str[ctrl]) == 99)
                    write(1, "Error\n",6);
                top--;
            }
            else
                write(1,"Error\n",6);
        }
        ctrl++;
    }
    if(top == 0)
        printf("%d\n",stack[top]);
    else
        write(1,"Error\n",6);
    return(0);
}
int     main(int ac, char **av)
{
    int stack[512];

    if (ac == 2)
        rpn_calc(av[1], stack);
    else
        write(1, "Error\n", 6);
    return (0);
}
