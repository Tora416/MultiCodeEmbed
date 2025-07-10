











#include "get_next_line.h"
#include <stdio.h>

void        my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void        draw_cube(int x, int y)
{
    int i;
    int j;

    i = x;
    j = y;
    while (j < g_tile_size + y)
    {
        while (i < g_tile_size + x)
        {
            my_mlx_pixel_put(&g_image, j, i, 0xFF0000);
            i++;
        }
        i = x;
        j++;
    }
}

void        norm_it(char **meh)
{
    int e;
    int f;
    int x;
    int y;

    e = 0;
    f = 0;
    x = 0;
    y = 0;
    while (meh[e])
    {
        while (meh[e][f])
        {
            if (meh[e][f] == '1')
                draw_cube(y, x);
            f++;
            x = x + g_tile_size;
        }
        f = 0;
        e++;
        x = 0;
        y = y + g_tile_size;
    }
}

void        draw_map(void)
{
    g_image.img = mlx_new_image(g_vars.mlx, g_width, g_height);
    g_image.addr = mlx_get_data_addr(g_image.img, &g_image.bits_per_pixel,
                    &g_image.line_length, &g_image.endian);
    norm_it(g_map_array);
}

int         has_wall(int x, int y)
{
    int ughx;
    int ughy;

    ughx = floor(x / g_tile_size);
    ughy = floor(y / g_tile_size);
    if (g_map_array[ughy][ughx] == '1')
        return (1);
    else
        return (0);
}
