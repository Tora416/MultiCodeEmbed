#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

void sequencia(int seq[], int print)
{
    int tam[10000], seq_aux[10000], qtd, k = 0, tam_s;
    for (int i = 0; seq[i] != 0; i++)
    {
        qtd = 0;
        for (int j = i; seq[j] == seq[i]; j++)
        {
            qtd++;
        }

        i += qtd - 1;
        tam[k] = qtd;
        seq_aux[k] = seq[i];
        k++;
    }

    for (int i = 0, j = 0, a = 0; j < k; a++)
    {
        if (a % 2 == 0)
        {
            seq[a] = tam[i];
            i++;
        }

        else if (a % 2 != 0)
        {
            seq[a] = seq_aux[j];
            j++;
        }

        if (print == true)
        {
            printf("%i", seq[a]);
        }
    }
}

int main()
{
    int seq[10000], n, tam_s; 

    seq[0] = 1;

    scanf("%i", &n);

    if (n == 1)
    {
        printf("%i\n", seq[0]);
    }

    else
    {
        for (int i = 1; i < n; i++)
        {
            if (i == (n - 1))
            {
                sequencia(seq, true);
                putchar('\n');
            }
            else
            {
                sequencia(seq, false);
            }
        }
    }

    return 0;
}