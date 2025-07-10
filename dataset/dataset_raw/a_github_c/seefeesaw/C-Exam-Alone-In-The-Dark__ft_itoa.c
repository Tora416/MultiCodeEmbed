











int     ft_len(int nb)
{
    int len;

    len = 1;
    if (nb < 0)
    {
        nb *= -1
        len++;
    }
    while (nb > 9)
    {
        nb /= 10;
        len++;
    }
    return (len);
}

int     ft_div(int nb)
{
    int div;
    div = 1;
    if (nb == 1)
        return (div);
    while (nb > 1)
    {
        div *= 10;
        nb--;
    }
    return (div);
}

char    *ft_itoa(int nbr)
{
    int     i;
    int     len;
    int     lne2;
    char    *res;

    len = ft_len(nbr);
    len2 = len;
    if (!(res = (char*)malloc(sizeof(char*) * (len + 1))))
        return (NULL);
    if (nbr == -2147483648)
        return ("-2147483648");
    i = 0;
    if (nbr < 0)
    {
        nbr *= -1;
        len--;
        res[0] = '-';
        i++;
    }
    while (i < len2)
    {
        res[i++] = (((nbr / ft_div(len--)) % 10) + 48);
    }
    res[i] = '\0';
    return (res);
}
