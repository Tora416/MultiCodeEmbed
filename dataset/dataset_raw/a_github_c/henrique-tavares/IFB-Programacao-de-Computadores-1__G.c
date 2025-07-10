#include <stdio.h>
#define true 1
#define false 0

int main ()
{
    long int num, primo = true, i = 3;
    scanf ("%li", &num);

    if (num == 1)
    {
        printf ("Composto!\n");
    }

    else if (num == 2)
    {
        printf ("Primo!\n");
    }

    else if ((num % 2) == 0)
    {
        printf ("Composto!\n");
    }

    else
    { 
        while (((i*i) <= num)&&(primo == true))
        {
            if ((num % i) == 0)
            {
                primo = false;
            }
            i += 2;
        }

        if (primo == true)
        {
            printf ("Primo!\n");
        }
        else
        {
            printf ("Composto!\n");
        }
    }

    return 0;
}