











#include "get_next_line.h"

void        surrend_by_spaces(char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (map[i])
    {
        while (j < g_map_width + 2)
            j++;
        map[i][j] = '\0';
        i++;
        j = 0;
    }
    i = -1;
    while (map[++i])
        map[i][0] = ' ';
    i = -1;
    while (map[0][++i])
        map[0][i] = ' ';
    i = -1;
    while (map[g_map_height][++i])
        map[g_map_height + 1][i] = ' ';
    i = -1;
    while (map[++i])
        map[i][g_map_width + 1] = ' ';
}

void        fill_map(char **map)
{
    int i;
    int j;
    int x;
    int y;

    i = 1;
    j = 1;
    x = 0;
    y = 0;
    while (x < g_map_height)
    {
        while (y < g_map_width)
        {
            if (y < ft_strlen(g_map_array[x]))
                map[i][j] = g_map_array[x][y];
            else
                map[i][j] = ' ';
            y++;
            j++;
        }
        i++;
        x++;
        j = 1;
        y = 0;
    }
}

void        longuest_line(void)
{
    int i;
    int j;
    int max;

    i = 0;
    j = 0;
    max = 0;
    while (g_map_array[i])
    {
        while (g_map_array[i][j] != '\0')
            j++;
        i++;
        if (j > max)
            max = j;
        j = 0;
    }
    g_map_width = max;
}
