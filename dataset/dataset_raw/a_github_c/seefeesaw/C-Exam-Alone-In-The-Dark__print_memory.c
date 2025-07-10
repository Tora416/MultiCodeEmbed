











#include <unistd.h>

void    print_hex(unsigned char c)
{
    char    *radix;

    radix = "0123456789abcdef";
    write(1, &radix[c / 16], 1);
    write(1, &radix[c % 16], 1);
}

void    print_char(unsigned char c)
{
    if (c >= ' ' && c <= '~')
        write(1, &c, 1);
    else
        write(1, ".", 1);
}

void    print_memory(const void *addr, size_t size)
{
    unsigned char   *adr;
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    adr = (unsigned char*)addr;
    while (i < size)
    {
        j = 0;
        while (j < 16 && i+j < size)
        {
            print_hex(adr[i + j]);
            if (j%2)
                write(1," ",1);
            j++;
        }
        while (j < 16)
        {
            write(1, "  ", 2);
            if (j%2)
                write(1, " ",1);
            j++;
        }
        j = 0;
        while (j < 16 && i+j < size)
        {
            print_char(adr[i +j]);
            j++;
        }
        write(1,"\n",1);
        i += 16;
    }
}
