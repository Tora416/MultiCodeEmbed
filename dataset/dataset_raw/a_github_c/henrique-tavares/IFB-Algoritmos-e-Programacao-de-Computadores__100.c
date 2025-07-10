#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    float v0, alfa, g = 10, x, y, t_queda, x_max;
    int t;

    printf("\nInforme a velocidade inicial em m/s: ");
    scanf("%f", &v0);
    printf("\nInforme o ângulo do lançamentos em graus: ");
    scanf("%f", &alfa);

    alfa = alfa * 3.14 / 180;

    t_queda = (2 * v0 * sin(alfa)) / g;
    x_max = (pow(v0, 2) * sin(alfa * 2)) / g;

    printf("\n");

    for (t = 0; t <= fabs(t_queda); t++)
    {
        x = v0 * cos(alfa) * t;
        y = v0 * sin(alfa) * t - 0.5 * g * pow(t, 2);

        printf("t = %is: Altura = %.2fm, Alcance = %.2fm\n", t, y, x);

        sleep(1);
    }

    printf("t = %is: Altura = 0.00m, Alcance = %.2fm\n\n", t++, x_max);
}