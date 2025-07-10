#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

int main()
{
    char t[1002], p[102];
    int tamt, tamp, busca;

    fgets(t, 1002, stdin);
    fgets(p, 102, stdin);

    for (int i = 0; t[i] != '\0'; i++)
    {
        if (t[i] == '\n')
        {
            t[i] = '\0';
        }
    }

    for (int i = 0; p[i] != '\0'; i++)
    {
        if (p[i] == '\n')
        {
            p[i] = '\0';
        }
    }

    tamt = strlen(t);
    tamp = strlen(p);

    

    for (int i = 0; i <= (tamt - tamp); i++)
    {
        if (t[i] == p[0])
        {
            busca = true;
            for (int k = 0; k < tamp; k++)
            {
                if (t[i+k] != p[k])
                {
                    busca = false;
                    break;
                }
            }

            if (busca == true)
            {
                printf ("%i ", i);
            }
        }
    }

    printf("\n\n");
    return 0;
}