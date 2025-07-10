#include <stdio.h>
#include <stdlib.h>

typedef struct Complex
{
    float real;
    float imaginario;

} complex_t;

void le_complexs(complex_t *a, complex_t *b);
void imprime_complex(complex_t *c);

complex_t conjugado(complex_t a);
complex_t adicao(complex_t a, complex_t b);
complex_t subtracao(complex_t a, complex_t b);
complex_t multiplicacao(complex_t a, complex_t b);
complex_t divisao(complex_t a, complex_t b);

int main()
{
    complex_t a, b, c;
    int escolha;

    do
    {
        do
        {
            printf("\nCalculadora de números complexs:\n");
            printf("\n\t(1) Adição\n");
            printf("\t(2) Subtração\n");
            printf("\t(3) Multiplicação\n");
            printf("\t(4) Divisão\n");
            printf("\t(5) Sair\n");
            printf("\n\tDigite sua escolha: ");
            scanf("%i", &escolha);
            getchar();
            system("clear");

        } while (escolha != 1 && escolha != 2 && escolha != 3 && escolha != 4 && escolha != 5);


        switch (escolha)
        {
            case 1:
                le_complexs(&a, &b);
                c = adicao(a,b);
                imprime_complex(&c);
                break;
            
            case 2:
                le_complexs(&a, &b);
                c = subtracao(a,b);
                imprime_complex(&c);
                break;
            
            case 3:
                le_complexs(&a, &b);
                c = multiplicacao(a,b);
                imprime_complex(&c);
                break;
            
            case 4:
                le_complexs(&a, &b);
                c = divisao(a,b);
                imprime_complex(&c);
                break;
            
            case 5:
                return 0;
        }

        printf("\nPressione ENTER para continuar: ");
        getchar();
        system("clear");

    } while (escolha != 5);

    return 0;
}


void le_complexs(complex_t *a, complex_t *b)
{
    printf("\nDigite o 1º número:\n");
    
    printf("\t-> Real: ");
    scanf("%f", &a->real);
    getchar();

    printf("\t-> Imaginário: ");
    scanf("%f", &a->imaginario);
    getchar();

    printf("\nDigite o 2º número:\n");
    
    printf("\t-> Real: ");
    scanf("%f", &b->real);
    getchar();

    printf("\t-> Imaginário: ");
    scanf("%f", &b->imaginario);
    getchar();
}

void imprime_complex(complex_t *c)
{

    if (c->imaginario < 0)
    {
        printf("\nRes = %.2f %.2fi\n", c->real, c->imaginario);
    }

    else
    {
        printf("\nRes = %.2f +%.2fi\n", c->real, c->imaginario);
    }
}

complex_t conjugado(complex_t a)
{
    a.imaginario *= -1;

    return a;
}

complex_t adicao(complex_t a, complex_t b)
{
    complex_t c;
    
    c.real = a.real + b.real;
    c.imaginario = a.imaginario + b.imaginario;

    return c;
}

complex_t subtracao(complex_t a, complex_t b)
{
    complex_t c;

    c.real = a.real - b.real;
    c.imaginario = a.imaginario - b.imaginario;

    return c;
}

complex_t multiplicacao(complex_t a, complex_t b)
{
    complex_t c;

    c.real = (a.real * b.real) - (a.imaginario * b.imaginario);
    c.imaginario = (a.real * b.imaginario) + (a.imaginario * b.real);

    return c;
}

complex_t divisao(complex_t a, complex_t b)
{
    complex_t c, d;

    complex_t b2 = conjugado(b);

    d = multiplicacao(b, b2);
    c = multiplicacao(a, b2);

    c.real /= d.real;
    c.imaginario /= d.real;

    return c;
}