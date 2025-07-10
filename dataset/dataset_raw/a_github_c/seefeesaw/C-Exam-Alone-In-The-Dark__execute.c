











#include "header.h"

static int  check_empty(t_m *m)
{
    if (m->ac > 1)
        return (0);
    else
        return (1);
}

static void loop(t_m *m, int x, int y)
{
    if (y == m->ac)
        final_print(m);
    else if (m->av[y][x] == 0)
        loop(m, 0, y + 1);
    else
    {
        if (is_enemy(m, x, y))
        {
            m->enemy = m->av[y][x];
            check_enemy(m, x, y);
        }
        loop(m, x + 1, y);
    }
}

void        execute(t_m *m)
{
    if (!check_empty(m))
        loop(m, 0, 1);
    else
        write(1, "\n", 1);
}
