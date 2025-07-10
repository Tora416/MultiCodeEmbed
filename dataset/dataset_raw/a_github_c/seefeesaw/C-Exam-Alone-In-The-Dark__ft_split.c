











#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char    **ft_split(char *str)
{
    char    **tab;
    int i;
    int i2;
    int i3;

    i = 0;
    i2 = 0;
    tab = (char**)malloc(sizeof(char**) * 1000);
    while (str[i])
    {
        if (str[i] > 32)
        {
            i3 = 0;
            tab[i2] = (char*)malloc(sizeof(char*) * 1000);
            while (str[i] > 32)
            {
                tab[i2][i3] = str[i];
                i++;
                i3++;
            }
            tab[i2][i3] = '\0';
            i2++;
        }
        i++;
    }
    tab[i2] = 0;
    return (tab);
}
int     main(int ac, char **av)
{
    if (ac > 1)
    {
        char **a = ft_split(av[1]);
    
        printf("%s\n%s\n%s\n",a[0],a[1],a[2]);
    }
    return (0);
}
