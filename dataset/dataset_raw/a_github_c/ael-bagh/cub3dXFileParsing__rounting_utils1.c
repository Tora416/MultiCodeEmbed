











#include "get_next_line.h"

int     all_params(void)
{
    if (g_width != 0 && g_height != 0 && g_we != NULL && g_no != NULL
        && g_no != NULL && g_ea != NULL && g_fr != -1 &&
        g_fr != -1 && g_fg != -1 && g_fb != -1 && g_cr != -1 &&
        g_cg != -1 && g_cb != -1)
        return (1);
    return (0);
}

int     wrong_resolution(int width, int height)
{
    int w;
    int h;

    w = width;
    h = height;
    if (width > 2560)
        w = 2560;
    if (height > 1400)
        h = 1400;
    if (width <= 100 || height <= 100)
    {
        ft_putstr("Error:\nresolution is < 100 px!\n");
        exit(0);
    }
    get_resolution(w, h);
    return (1);
}

void    get_resolution(int width, int height)
{
    g_width = width;
    g_height = height;
}

void    get_frgb(int r, int g, int b)
{
    g_fr = r;
    g_fg = g;
    g_fb = b;
}

void    get_crgb(int r, int g, int b)
{
    g_cr = r;
    g_cg = g;
    g_cb = b;
}
