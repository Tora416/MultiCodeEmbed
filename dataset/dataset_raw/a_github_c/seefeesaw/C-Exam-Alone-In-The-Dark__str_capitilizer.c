











#include <unistd.h>

int     ft_toupper(char  a,char b)
{
    if ( a == ' ' || a == '\t')
    {
        if (b >= 'a' && b <= 'z')
            return (1);
    }
    return (0);
}

int     ft_tolower(char a, char b, int i)
{
    if (a != ' ' && a != '\t' && i != -1)
    {
        if (b >= 'A' && b <= 'Z')
            return (1);
    }
    return (0);
}

int     main(int ac, char **av)
{
    int i;
    int j;
    if (ac > 1)
    {
        i = 1;
        while (i < ac)
        {

            
            j = 0;
            while (av[i][j])
            {
                if (av[i][0] >= 'a' && av[i][0] <= 'z')
                    av[i][0] -= 32;
                else if (ft_tolower(av[i][j - 1], av[i][j], j - 1))
                    av[i][j] += 32;
                else if (ft_toupper(av[i][j - 1] , av[i][j]))
                    av[i][j] -= 32;
                write(1, &av[i][j], 1);
                j++;
            }
            i++;
            write(1, "\n", 1);
        }
    }
    else
        write(1, "\n",1);
    return (0);
}
