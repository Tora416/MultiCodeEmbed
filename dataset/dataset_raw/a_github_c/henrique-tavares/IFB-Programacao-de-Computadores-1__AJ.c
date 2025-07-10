#include <stdio.h>
#include <limits.h>
#define true 1
#define false 0

int primos(long int maior, long int vet[])
{
    long int primo = 3;
    int busca, i0;
    vet[0] = 2;
    for (int i = i; (vet[i] * vet[i]) <= maior;)
    {
        busca = true;
        for (int j = i; (j >= 0) && (busca == true); j--)
        {
            if (primo % vet[j] == 0)
                busca = false;
        }

        if (busca == true)
        {
            vet[i + 1] = primo;
            i++;
            i0 = i;
        }

        else if (busca == false)
            primo++;
    }

    return i0;
}

int primo(long int num, long int vet[], int tam)
{    
    if (num == 1) return false;

    else if (num == 2) return true;
        
    else
    {
        for (int j = 0; j <= tam; j++)
        {
            if ((num % vet[j] == 0) && (num != vet[j]))
                return false;
        }
    }

    return true;
}

int main(int argc, char **argv)
{
    int t, tam, primovf;
    long int n[200000], maior = 0, n0, vet[10000];

    scanf("%i", &t);

    for (int i = 0; i < t; i++)
    {
        scanf("%li", &n[i]);

        if (n[i] > maior)
            maior = n[i];
    }

    tam = primos(maior, vet);

    for  (int i = 0; i < t; i++)
    {
        primovf = primo(n[i], vet, tam);

        n0 = n[i];

        while (primovf == true && n[i] >= 10)
        {
            n[i] /= 10;
            
            primovf = primo(n[i], vet, tam);
        }

        if (primovf == true)
            printf("S\n");
        
        else if (primovf == false)
            printf("N\n");
    }    

    return 0;
}