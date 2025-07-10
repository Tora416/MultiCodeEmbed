











#include "header.h"

static int  ft_strlen(char *s)
{
    int i;

    i = 0;
    if (s != 0)
    {
        while (s[i])
        {
            ++i;
        }
    }
    return (i);
}

t_m         m_init(int ac, char **av)
{
    t_m m;

    m.debug = 1;
    m.ac = ac;
    m.av = av;
    m.len = ft_strlen(av[1]);
    m.enemy = 0;
    m.mate = 0;
    m.act_x = 0;
    m.act_y = 0;
    m.off_x = 0;
    m.off_y = 0;
    return (m);
}
