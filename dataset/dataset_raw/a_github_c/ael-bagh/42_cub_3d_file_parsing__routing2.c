











#include "get_next_line.h"

int     str_is_digits(char *c)
{
    int i;

    i = 0;
    if (!c)
        return (0);
    while (c[i])
    {
        if (!ft_isdigit(c[i]))
            return (0);
        i++;
    }
    return (1);
}

int     array_is_rgb(char **colors)
{
    int i;

    i = 0;
    while (colors[i])
    {
        if (str_is_digits(colors[i]))
        {
            if (!(atoi(colors[i]) <= 255) || !(atoi(colors[i]) >= 0))
            {
                ft_putstr("Error\n Wrong colors parametres!");
                exit(0);
            }
        }
        else
            return (0);
        i++;
    }
    return (1);
}

void    get_s(char *line)
{
    char    **par;
    char    *str;
    int     re;

    re = 0;
    par = ft_split(line, ' ');
    str = ft_strdup("");
    if (g_s != NULL)
        texture_error(0);
    if (c_w(line, ' ') != 2)
    {
        while (++re < c_w(line, ' '))
        {
            str = ft_strjoin(str, &par[re][0]);
            if (re != c_w(line, ' ') - 1)
                str = ft_strjoin(str, " ");
        }
        if ((re = open(str, O_RDONLY) < 0))
            texture_error(5);
        else
            g_s = ft_strdup(str);
    }
    else
        wrong_file(&par[1][0], 5);
    free_this_shit(str, par);
}

void    get_f(char *line)
{
    char    **par;
    char    **colors;
    int     cc;
    int     cw;

    cw = 0;
    par = ft_split(line, ' ');
    cc = 0;
    colors = ft_split(&par[1][0], ',');
    while (line[cc])
    {
        if (line[cc] == ',')
            cw++;
        cc++;
    }
    if (cw != 2)
    {
        ft_putstr("Error:\n Wrong floor RGB");
        exit(0);
    }
    cw = c_w(line, ' ');
    cc = c_w(&par[1][0], ',');
    freethenipples(par);
    check_frgb(colors, cc, cw);
    freethenipples(colors);
}

void    get_c(char *line)
{
    char    **par;
    char    **colors;
    int     cc;
    int     cw;

    cw = 0;
    par = ft_split(line, ' ');
    cc = 0;
    colors = ft_split(&par[1][0], ',');
    while (line[cc])
    {
        if (line[cc] == ',')
            cw++;
        cc++;
    }
    if (cw != 2)
    {
        ft_putstr("Error:\n Wrong ceiling RGB");
        exit(0);
    }
    cw = c_w(line, ' ');
    cc = c_w(&par[1][0], ',');
    freethenipples(par);
    check_crgb(colors, cc, cw);
    freethenipples(colors);
}
