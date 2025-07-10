











#include "get_next_line.h"

void    global_init(void)
{
    g_no = NULL;
    g_so = NULL;
    g_we = NULL;
    g_ea = NULL;
    g_width = 0;
    g_height = 0;
    g_fr = -1;
    g_fg = -1;
    g_fb = -1;
    g_cr = -1;
    g_cg = -1;
    g_cb = -1;
    g_map_started = 0;
    g_map = ft_strdup("");
}

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        ft_putchar(str[i]);
        i++;
    }
}

int     ft_isdigit(int c)
{
    if (c >= 0x30 && c <= 0x39)
        return (1);
    return (0);
}

char    *ft_strjoi(char *s1, char *s2)
{
    char    *str;
    int     i;
    int     j;

    if (!s2)
        return (s1);
    if (!s1)
        return (s2);
    str = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
    i = -1;
    while (s1[++i])
    {
        str[i] = s1[i];
    }
    j = -1;
    while (s2[++j])
    {
        str[i] = s2[j];
        i++;
    }
    str[i] = '\n';
    str[i + 1] = '\0';
    free(s1);
    return (str);
}
