











#include "list.h"
#include <stdlib.h>

int     cycle_detector(const t_list *list)
{
    const t_list *p;
    const t_list *q;

    p = list;
    q = list;
    while (p && q && q->next)
    {
        p = p->next;
        q = q->next->next;
        if (p == q)
            return (1);
    }
    return (0);
}
