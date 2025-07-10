#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char str[82];
    int num[100000], k, n, tam;
    long int tam_total = 0;

    scanf("%i", &n);
    scanf("%i", &k);
    getchar();

    for (int j = 0; j < n; j++)
    {
        fgets(str, 82, stdin);

        for (int i = 0; str[i] != '\0'; i++)
        {
            if (str[i] == '\n')
            {
                num[i + tam_total] = ((int)str[i]);
            }

            else
            {
                num[i + tam_total] = ((int)str[i]) - k;

                if (num[i + tam_total] < 32)
                {
                    num[i + tam_total] += 95;
                }
            }
        }

        tam = strlen(str);
        tam_total += tam;
    }

    for (long int i = 0; i < tam_total; i++)
    {
        printf("%c", num[i]);
    }

    return 0;
}