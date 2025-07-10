#include <stdlib.h>

char *get_int(int num);
unsigned int _abs(int);
int get_numbase_len(unsigned int num, unsigned int base);
void fill_numbase_buff(unsigned int num, unsigned int base,
        char *buff, int buff_size);


char *get_int(int num)
{
    unsigned int temp;
    int length = 0;
    long num_l = 0;
    char *ret;

    temp = _abs(num);
    length = get_numbase_len(temp, 10);

    if (num < 0 || num_l < 0)
        length++; 
    ret = malloc(length + 1); 
    if (!ret)
        return (NULL);

    fill_numbase_buff(temp, 10, ret, length);
    if (num < 0 || num_l < 0)
        ret[0] = '-';

    return (ret);
}


unsigned int _abs(int i)
{
    if (i < 0)
        return (-(unsigned int)i);
    return ((unsigned int)i);
}


int get_numbase_len(unsigned int num, unsigned int base)
{
    int len = 1; 

    while (num > base - 1)
    {
        len++;
        num /= base;
    }
    return (len);
}


void fill_numbase_buff(unsigned int num, unsigned int base,
        char *buff, int buff_size)
{
    int rem, i = buff_size - 1;

    buff[buff_size] = '\0';
    while (i >= 0)
    {
        rem = num % base;
        if (rem > 9) 
            buff[i] = rem + 87; 
        else
            buff[i] = rem + '0';
        num /= base;
        i--;
    }
}
