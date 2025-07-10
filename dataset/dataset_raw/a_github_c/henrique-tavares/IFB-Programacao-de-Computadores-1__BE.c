#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char str[90];
    int num[100000], k, n, tam, tam_total = 0;

    scanf("%i", &n);
    scanf("%i", &k);
    getchar();

    for (int j = 0; j < n; j++)
    {
        fgets(str, 90, stdin);

        for (int i = 0; str[i] != '\0'; i++)
        {
            if (str[i] == '\n')
            {
                num[i + tam_total] = ((int)str[i]);
            }
            else
            {
                num[i + tam_total] = ((int)str[i]) + k;
            }

            if (num[i + tam_total] > 126)
            {
                num[i + tam_total] -= 95;
            }

            
        }

        tam = strlen(str);
        tam_total += tam;
    }

    for (int i = 0; i < tam_total; i++)
    {
        printf("%c", num[i]);
    }

    return 0;
}