











#include <unistd.h>

int     main(int argc, char **argv)
{
    int i = 1;
    int t[32] = {0};
    int j = 0;

    if (argc == 1)
    {
        write(1, "options: abcdefghijklmnopqrstuvwxyz\n", 36);
        return (0);
    }
    i = 1;
    while (i < argc)
    {
        j = 1;
        if (argv[i][0] == '-')
        {
            while (argv[i][j] && argv[i][j] >= 'a' && argv[i][j] <= 'z')
            {
                if (argv[i][j] == 'h')
                {
                    write(1, "options: abcdefghijklmnopqrstuvwxyz\n", 36);
                    return (0);
                }
                t['z' - argv[i][j] + 6] = 1;
                j++;
            }
            if (argv[i][j])
            {
                write(1, "Invalid Option\n", 15);
                return (0);
            }
            j++;
        }
        i++;
    }
    i = 0;
    while (i < 32)
    {
        t[i] = '0' + t[i];
        write(1, &t[i++], 1);
        if (i == 32)
            write(1, "\n", 1);
        else if (i % 8 == 0)
            write(1, " ", 1);
    }
    return (0);
}
