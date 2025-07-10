











#include "get_next_line.h"
#include <stdio.h>

int     readline(void)
{
    int     fd;
    char    *line;

    fd = open("map.cub", O_RDONLY);
    global_init();
    while (get_next_line(fd, &line))
    {
        if (!all_params())
        {
            if (*line != '\0')
                routing(line);
        }
        else
            routing(line);
        free(line);
    }
    free(line);
    return (0);
}

void    routing(char *line)
{
    if (line[0] == 'R' && line[1] == ' ')
        get_re(line);
    else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
        get_no(line);
    else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
        get_so(line);
    else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
        get_we(line);
    else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
        get_ea(line);
    else if (line[0] == 'S' && line[1] == ' ')
        get_s(line);
    else if (line[0] == 'F' && line[1] == ' ')
        get_f(line);
    else if (line[0] == 'C' && line[1] == ' ')
        get_c(line);
    else if (all_params())
        readmap(line);
    else
    {
        ft_putstr("one or many parametres format is wrong or missing!\n");
        exit(0);
    }
}

int     main(void)
{
    char **ugh;
    int a;
    readline();
    manage_map();
    longuest_line();
    array_height();
    ugh = map_manager();
    g_vars.mlx = mlx_init();
    g_vars.win = mlx_new_window(g_vars.mlx, g_width, g_height, "Bismilah!");
    
    
    freethenipples(ugh);
    mlx_loop_hook(g_vars.mlx, move, 0);
    mlx_loop(g_vars.mlx);
}
