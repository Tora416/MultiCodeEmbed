











#include <unistd.h>
#include <stdio.h>

int     main(int ac, char **av)
{
    int     i;
    int     j;
    int     count;

    count = 0;
    i = 0;
    j = 0;
    if (ac == 3)
    {
        while (av[1][i] != '\0')
        {
            while (av[2][j] != '\0')
            {
                if (av[1][i] == av[2][j])
                {
                    count++;
                    break;
                }
                j++;
            }
            i++;
        }
        if (av[1][count] == '\0')
            write(1, "1", 1);
        else
            write(1, "0", 1);
    }
    write(1, "\n", 1);
    return (0);
}
