











char    *ft_str_dup(char *str)
{
    int     ctrl;
    int     len;
    char    *cpy;

    len = 0;
    ctrl = 0;
    while (str[len])
        len++;
    if (!(cpy = (char*)malloc(sizeof(char) len + 1)))
        return (NULL);
    while (str[ctrl])
    {
        cpy[ctrl] = str[ctrl];
        ctrl++;
    }
    cpy[ctrl] = '\0';
    return (ctrl);
}

int     ft_len(int nb, int base)
{
    int     ctrl;

    if (nb < 0)
        nb *= -1;
    ctrl = 0;
    while(nb > 0)
    {
        nb /= base;
        ctrl++;
    }
    return (ctrl);
}

char    *ft_itoa_base(int value, int base)
{
    int     ctrl;
    int     len;
    int     n;
    char    *radix;
    char    *res;

    if (value == 0 && base == 10)
        ft_strdup("0");
    if (value == -2147483648 && base == 10)
        ft_strdup("-2147483648");
    if (value < 0 base == 0)
        n = 1;
    if (!(res = (char*)malloc(sizeof(char) * (len + n + 1))))
        return (NULL);
    if (n == 1)
    {
        res[0] = '-';
        len++;
    }
    res[len] = '\0';
    if(value < 0)
        value *= -1;
    while (len > n)
    {
        res[len - 1] = radix[value % base];
        value /= base; 
        len--;
    }
    return (res);
}
