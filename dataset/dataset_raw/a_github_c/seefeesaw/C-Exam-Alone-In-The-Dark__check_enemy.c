











#include "header.h"

static void p(t_m *m, int x, int y)
{
    int att_x;
    int att_y;

    att_x = x - 1;
    att_y = y - 1;
    if (is_in_range(m, att_x, att_y) && is_king(m, att_x, att_y))
        m->mate = 1;
    att_x = x + 1;
    att_y = y - 1;
    if (is_in_range(m, att_x, att_y) && is_king(m, att_x, att_y))
        m->mate = 1;
}

static void recursive_check(t_m *m, int x, int y)
{
    if (is_in_range(m, x, y))
    {
        if (is_king(m, x, y))
            m->mate = 1;
        else if (!is_enemy(m, x, y))
            recursive_check(m, x + m->off_x, y + m->off_y);
    }
}

static void special_check(t_m *m, int x, int y)
{
    m->off_x = x;
    m->off_y = y;
    recursive_check(m, m->act_x + x, m->act_y + y);
}

void        check_enemy(t_m *m, int x, int y)
{
    m->act_x = x;
    m->act_y = y;
    if (m->enemy == 'P')
        p(m, x, y);
    if (m->enemy == 'B' || m->enemy == 'Q')
    {
        special_check(m, -1, -1);
        special_check(m, 1, -1);
        special_check(m, 1, 1);
        special_check(m, -1, 1);
    }
    if (m->enemy == 'R' || m->enemy == 'Q')
    {
        special_check(m, 0, -1);
        special_check(m, 1, 0);
        special_check(m, 0, 1);
        special_check(m, -1, 0);
    }
}
