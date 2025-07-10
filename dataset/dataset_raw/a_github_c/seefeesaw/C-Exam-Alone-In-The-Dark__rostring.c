











#include <unistd.h>
#include <stdlib.h>

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    while(str[i])
        write(1, &str[i++], 1);
}

char    **ft_split(char *str)
{
    int i;
    int i2;
    int i3;
    char **tab;

    i = 0;
    i2 = 0;
    tab = (char**)malloc(sizeof(char*) * 1000);
    while(str[i])
    {
        if (str[i] > 32)
        {
            i3 = 0;
            tab[i2] = (char*)malloc(sizeof(char*) * 1000);
            while (str[i] > 32)
                tab[i2][i3++] = str[i++];
            tab[i2++][i3] = '\0';
        }
        else
            i++;
    }
    tab[i2] = 0;
    return (tab);
}
int     main(int ac, char **av)
{
    int i;
    char    **word;

    i = 1;
    if(ac == 2)
    {
        word = ft_split(av[1]);
        while (word[i] != 0)
        {
            ft_putstr(word[i++]);
            write(1, " ", 1);
        }
        ft_putstr(word[0]);
    }
    write(1, "\n",1);
    return (0);
}
