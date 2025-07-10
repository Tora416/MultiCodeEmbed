











#include <unistd.h>

int     matching(char b1, char b2)
{
    if (b1 == '(' && b2 == ')')
        return (1);
    if (b1 == '[' && b2 == ']')
        return (1);
    if (b1 == '{' && b2 == '}')
        return (1);
    return (0);
}

int     brackets(char   *str, char *store)
{
    int     ctrl;
    int     top;

    ctrl = 0;
    top = -1;
    while (str[ctrl])
    {
        if (str[ctrl] == '(' || str[ctrl] == '[' || str[ctrl] == '{')
        {
            top++;
            store[top] = str[ctrl];
        }
        if (str[ctrl] == ')' || str[ctrl] == ']' || str[ctrl] == '}')
        {
            if (!store[top])
                return(0);
            if (!matching(store[top],str[ctrl]))
                return (0);
            else
            {
                store[top] = 0;
                top--;
            }
        }
        ctrl++;
    }
    if (store[top] == 0)
        return(1);
    return (0);
}

int     main(int ac, char **av)
{
    char    store[500];

    if (ac > 1)
    {
        if (brackets(av[1],store))
            write(1, "OK",2);
        else
            write(1, "Error",5);
    }
    write(1,"\n",1);
    return(0);
}
