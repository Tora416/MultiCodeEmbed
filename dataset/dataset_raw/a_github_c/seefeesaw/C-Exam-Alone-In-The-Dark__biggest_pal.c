











#include <unistd.h>
#include "biggest_pal.h"

int     ft_strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

void        ft_putstr(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        write(1, &str[i], 1);
        i++;
    }
}

void        pal(char *str)
{
    t_pal   pal;
    t_pal   count;
    t_pal   old;
    int     i = 0;
    int     max;

    count.end = ft_strlen(str) - 1;
    max = count.end;
    while (str[i] != '\0')
    {
        count.length = 1;
        count.start = i;
        old.start = i;
        old.end = count.end;
        max = count.end;
        while (str[count.start] == str[count.end])
        {
            if (count.start == count.end || count.start + 1 == count.end)
            {
                if (old.end - old.start >= pal.length)
                {
                    pal.start = old.start;
                    pal.end = old.end + 1;
                    pal.length = old.end - old.start;
                }
                break ;
            }
            count.length++;
            count.start++;
            count.end--;
        }
        count.start = old.start;
        count.end = old.end;
        if (max == pal.length)
            break ;
        if (str[i + 1] == '\0' && count.end > 0)
        {
            count.end--;
            i = -1;
        }
        i++;
    }
    if (pal.length == 0)
    {
        ft_putstr(&str[ft_strlen(str) - 1]);
        return ;
    }
    str[pal.end] = '\0';
    ft_putstr(&str[pal.start]);
}

int         main(int ac, char **av)
{

    if (ac == 2)
    {
        pal(av[1]);
    }
    ft_putstr("\n");
    return (0);
}
