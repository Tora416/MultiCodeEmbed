











#include "get_next_line.h"

void    check_crgb(char **colors, int cc, int cw)
{
    if (g_cr != -1 && g_cg != -1 && g_cb != -1)
    {
        ft_putstr("Error\ndouble includion\n");
        exit(0);
    }
    if (cc != 3 || cw != 2)
    {
        ft_putstr("Error\nWrong number of parametres in ceiling colors!\n");
        exit(0);
    }
    else if (!array_is_rgb(colors))
    {
        ft_putstr("Error\nWrong parametres in ceiling colors!\n");
        exit(0);
    }
    else
        get_crgb(atoi(&colors[0][0]), atoi(&colors[1][0]), atoi(&colors[2][0]));
}

void    check_frgb(char **colors, int cc, int cw)
{
    if (g_cr != -1 && g_cg != -1 && g_cb != -1)
    {
        ft_putstr("Error\ndouble includion\n");
        exit(0);
    }
    if (cc != 3 || cw != 2)
    {
        ft_putstr("Error\nWrong number of parametres in floor colors!\n");
        exit(0);
    }
    else if (!array_is_rgb(colors))
    {
        ft_putstr("Error\nWrong parametres in floor colors!\n");
        exit(0);
    }
    else
        get_frgb(atoi(&colors[0][0]), atoi(&colors[1][0]), atoi(&colors[2][0]));
}
