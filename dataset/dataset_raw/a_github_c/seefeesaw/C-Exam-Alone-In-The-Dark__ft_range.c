











#include <stdlib.h>
#include <stdio.h>

int     ft_abs(int a)
{
    if (a < 0)
        return (-a);
    return (a);
}

int     *ft_range(int start, int end)
{
    int     *tab;
    int     i;

    i = 0;
    if (!(tab = (int*)malloc(sizeof(int*) *ft_abs (start - end) + 1)))
        return (NULL);
    if (start > end)
    {
            while (start >= end)
        {
            tab[i] = start--;
            i++;
        }
        tab[i] = '\0';
    }
    else if (start < end)
    {
        while (start <= end)
        {
            tab[i] = start++;
            i++;
        }
        tab[i] = '\0';
    }
    return (tab);
}

int main()
{
    int a = 0;
    int b = -3;

    int     i;
    i = 0;
    int *tab =ft_range(a,b);
    while (tab[i])
    {
        printf("%d ",tab[i]);
        i++;
    }
    printf("%d ",tab[i]);
    i++;
    while (tab[i])
    {
        printf("%d ",tab[i]);
        i++;
    }
    return (0);
}
