











#include <unistd.h>

void        ft_putchar(char c)
{
    write(1, &c, 1);
}

void        ft_putnbr(int nb)
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
    int     res;

    i = 0;
    res = 0;
    while (str[i])
    {
        res *= 10;
        res = str[i] - 48;
        i++;
    }
    return (res);
}

int     ft_is_prime(int nb)
{
    int i;

    i = 2;
    while (i < nb)
    {
        if (nb % i == 0)
            return (0);
        i++;
    }
    return (1);
}

int     ft_add_prime_sum(int nb)
{
    int     i;
    int     sum;

    i = 2;
    sum = 0;
        if (nb <= 0)
            return (0);
    while (i <= nb)
    {
        if (ft_is_prime(i))
            sum += i;
        i++;
    }
    return (sum);
}

int     main(int ac, char **av)
{
    if (ac == 2)
        ft_putnbr(ft_add_prime_sum(ft_atoi(av[1])));
    else if (ac != 2 || ft_atoi(av[1]) < 0)
        write(1, "0", 1);
    write(1, "\n", 1);
    return (0);
}
