#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Pontos
{
    double x;
    double y;

} pontos_t;

double fatorial(int n);
void le_poligono(pontos_t *poligono, int n);
double perimetro(pontos_t *poligono, int n);
double area(pontos_t *poligono, int n);
double triangulos(pontos_t *poligono, int n, int m);

int main()
{
    int n;

    do
    {
        printf("\nDigite o número de lados do polígono (>= 3): ");
        scanf("%li", &n);

        if (n < 3) system("clear");

    } while (n < 3);

    pontos_t *poligono = malloc(n * sizeof(pontos_t));

    le_poligono(poligono, n);

    system("clear");

    printf("\n\tPerímetro = %lf\n", perimetro(poligono, n));
    printf("\n\tÁrea = %lf\n", area(poligono, n));
    printf("\n\tQuantidade de triângulos possíveis = %.0lf\n\n", triangulos(poligono, n, 3));

    free(poligono);

    return 0;
}

double fatorial(int n)
{
    return (n > 0) ? n * fatorial(n-1) : 1;
}

void le_poligono(pontos_t *poligono, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nDigite as coordenadas do %liº ponto:\n", i+1);

        printf("\t-> Coordenada x: ");
        scanf("%lf", &poligono[i].x);
        getchar();

        printf("\t-> Coordenada y: ");
        scanf("%lf", &poligono[i].y);
        getchar();
    }
}

double perimetro(pontos_t *poligono, int n)
{
    double perimetro = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == n-1)
        {
            perimetro += sqrtf(powf(poligono[i].x - poligono[0].x,2) + powf(poligono[i].y - poligono[0].y,2));
        }

        else
        {
            perimetro += sqrtf(powf(poligono[i].x - poligono[i+1].x,2) + powf(poligono[i].y - poligono[i+1].y,2));
        }
    }

    return perimetro;
}

double area(pontos_t *poligono, int n)
{
    double area = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == n-1)
        {
            area += (poligono[i].x * poligono[0].y) - (poligono[0].x * poligono[i].y);
        }

        else
        {
            area += (poligono[i].x * poligono[i+1].y) - (poligono[i+1].x * poligono[i].y);
        }
    }

    area /= 2;

    return (area < 0) ? area*(-1) : area;
}

double triangulos(pontos_t *poligono, int n, int m)
{
    double triangulos;

    triangulos = fatorial(n) / (fatorial(n-m) * fatorial(m));

    return triangulos;
}