











#include "get_next_line.h"

double      normalangle(double rayangle)
{
    rayangle = fmod(rayangle, (2 * M_PI));
    return (rayangle);
}

void        update(void)
{
    float   newx;
    float   newy;
    float   move_step;

    g_player.rotation_angle += g_player.turn_direction *
                                g_player.rotation_speed;
    move_step = g_player.walk_direction * g_player.move_speed;
    newx = g_player.x + cos(g_player.rotation_angle) * move_step;
    newy = g_player.y + sin(g_player.rotation_angle) * move_step;
    if (!has_wall(newx, newy))
    {
        g_player.x = newx;
        g_player.y = newy;
    }
}

void        render(void)
{
    update();
    draw_map();
    cast_rays();
    mlx_put_image_to_window(g_vars.mlx, g_vars.win, g_image.img, 0, 0);
    mlx_destroy_image(g_vars.mlx, g_image.img);
}

int         key_press(int keycode)
{
    if (keycode == 13)
        g_player.walk_direction = 1;
    if (keycode == 1)
        g_player.walk_direction = -1;
    if (keycode == 0)
        g_player.turn_direction = -1;
    if (keycode == 2)
        g_player.turn_direction = 1;
    return (0);
}

int         key_release(int keycode)
{
    if (keycode == 13)
        g_player.walk_direction = 0;
    if (keycode == 1)
        g_player.walk_direction = 0;
    if (keycode == 0)
        g_player.turn_direction = 0;
    if (keycode == 2)
        g_player.turn_direction = 0;
    return (0);
}

int         move(void)
{
    mlx_hook(g_vars.win, 2, 0, key_press, &g_vars);
    render();
    mlx_hook(g_vars.win, 3, 0, key_release, &g_vars);
    return (0);
}
