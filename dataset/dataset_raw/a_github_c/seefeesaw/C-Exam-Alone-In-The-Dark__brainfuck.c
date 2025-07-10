











#include <stdlib.h>
#include <unistd.h>

int     counter(char *src, int ctrl)
{
    int dir;
    int count;
    count = 0;

    if (src[ctrl] == '[')
        dir = 1;
    if (src[ctrl] == ']')
        dir = -1;
    while(src[ctrl])
    {
        if (src[ctrl] == '[')
            count++;
        if (src[ctrl] == ']')
            count--;
        if ((src[ctrl] == '[' || src[ctrl] == ']') && count == 0)
            return (ctrl);
        ctrl += dir;
    }
    return (0);
}

void    brainfuck(char *src)
{
    char    *str;
    int     pointer;
    int     ctrl;

    ctrl = 0;
    pointer = 0;
    str = (char*)malloc(sizeof(char) * 2048);
    while (src[ctrl])
    {
        if (src[ctrl] == '>')
            pointer++;
        else if (src[ctrl] == '<')
            pointer--;
        else if (src[ctrl] == '+')
            str[pointer]++;
        else if (src[ctrl] == '-')
            str[pointer]--;
        else if ((src[ctrl] == '[' && !str[pointer]) || (src[ctrl] == ']' && str[pointer]))
                ctrl = counter(src, ctrl);
        else if (src[ctrl] == '.')
            write(1, &str[pointer], 1);
        ctrl++;
    }
}
int     main(int argc, char **av)
{
    if (argc > 1)
        brainfuck(av[1]);
    else
        write(1, "\n", 1);
    return (0);
}
