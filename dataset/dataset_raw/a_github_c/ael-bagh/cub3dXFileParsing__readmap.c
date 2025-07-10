











#include "get_next_line.h"

int     check_char(char *mapline, char c)
{
    int i;

    i = 0;
    while (mapline[i])
    {
        if (mapline[i] != c)
            return (0);
        i++;
    }
    return (1);
}

void    readmap(char *line)
{
    if (line[0] != '\0' && !g_map_started)
        g_map_started = 1;
    if (g_map_started && line[0] != '\0')
    {
        g_map = ft_strjoi(g_map, line);
    }
    if (g_map_started && line[0] == '\0')
    {
        ft_putstr("Error:\nmap has a new line");
        exit(0);
    }
}

void    manage_map(void)
{
    g_map_array = ft_split(g_map, '\n');
}

int     begins_by_nl(char **mapline)
{
    int i;

    i = 0;
    while (mapline[i] != '\0')
    {
        if (mapline[i][0] == '\n')
            return (1);
        i++;
    }
    return (0);
}
