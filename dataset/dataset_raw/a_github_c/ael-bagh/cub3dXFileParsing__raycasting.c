











#include "get_next_line.h"
#include <stdio.h>

void        cast_ray(int l, float angle)
{
    float   i;
    float   j;
    float   xp;
    float   yp;

    i = 0;
    while (i < l)
    {
        xp = cos(angle) * i + g_player.x;
        yp = sin(angle) * i + g_player.y;
        i++;
        my_mlx_pixel_put(&g_image, xp, yp, 0xFF0000);
    }
}

void        cast_rays(void)
{
    int     strip_id;
    float   angle;

    strip_id = 0;
    angle = g_player.rotation_angle - (g_player.fov / 2);
    while (strip_id < g_width)
    {
        normalangle(angle);
        cast_ray(50, (float)angle);
        angle += g_player.fov / g_width;
        strip_id++;
    }
}
