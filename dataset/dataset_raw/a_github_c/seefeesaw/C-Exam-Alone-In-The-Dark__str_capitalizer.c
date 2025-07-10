











#include <unistd.h>

int     toupperr(char a, char d)
{
    if (a >= 'a' && a <= 'z')
    {
        if (d  == ' ' || d == '\t' || d == '\0')
            return (1);
    }
    return(0);
}

int     tolowerr(char a, char d)
{
    if (a >= 'A' && a <= 'Z')
    {
        if (d != ' ' && d != '\t' && d != '\0')
        {
            return (1);
        }
    }
    return (0);
}

int     main(int ac,char **av)
{
    int     i;
    int     i2;

    i = 0;
    if (ac > 1)
    {
        while (i < ac)  
        {
            i++;
            i2 = 0;
            while (av[i][i2])
            {
                if (tolowerr(av[i][i2], av[i][i2 + 1]))
                    av[i][i2] += 32;
                else if (toupperr(av[i][i2] , av[i][i2 + 1]))
                    av[i][i2] -= 32;
                write(1, &av[i][i2], 1);
                i2++;
            }
            i++;
            write(1, "\n", 1);
        }
    }
    else
        write(1, "\n",1);
    return(0);
}
