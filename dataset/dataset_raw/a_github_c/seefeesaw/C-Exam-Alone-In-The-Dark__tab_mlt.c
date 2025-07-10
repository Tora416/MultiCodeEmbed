











#include <unistd.h>
#include <stdio.h>

void    ft_putchar(char c)
{
    write(1, &c,1);
}

void    ft_putnbr(int nb)
{
    if (nb < 0)
        nb *= -1;
    if (nb > 9)
    {
        ft_putnbr(nb / 10);
        ft_putnbr(nb % 10);
    }
    else
        ft_putchar(nb + 48);
}

int     ft_atoi(char *str)
{
    int     i;
    int     sign;
    int     res;

    sign = -1;
    res = 0;
    if (str[0] == '-')
        sign *= -1;
    i = 0;
    while (str[i])
    {
        res = res * 10 + (str[i] - 48);
        i++;
    }
    return (res * sign);
}

int     main(int    ac,char **av)
{
    int     n;
    int     i;

    if (ac == 2)
    {
        n = ft_atoi(av[1]);
        i = 1;
        while (i <= 9)
        {
            ft_putnbr(i);
            write(1, " x ", 3);
            ft_putnbr(n);
            write(1, " = ", 3); 
            ft_putnbr(i * n);
            write(1, "\n", 1);
            i++;
        }
    }
    else
        write(1 , "\n", 1);
    return (0);
}
