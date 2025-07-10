#include<stdio.h>
#include<math.h>

void calcolo_ipotenusa(float *ac, float *gamma, float *ipotenusa)
{
    double angolo_gamma = *gamma;
    *ipotenusa = *ac / sin(angolo_gamma);  
           
}

float calcolo_perimetro(float ac, float ipotenusa, float *bc)
{
   return ac + ipotenusa + *bc;
}

void calcolo_area(float *perimetro, float ac, float *ipotenusa, float *bc, float *area)
{
    double parziale = (*perimetro/2) * (*perimetro/2 - ac) * (*perimetro/2 - *ipotenusa) * (*perimetro/2 - *bc);

    *area = sqrt(parziale);
}

float calcolo_altezza(float *ab, float *h)
{
    return ((*ab * *h) / 2);
}

int main(void) 
{
    float ac, gamma, bc=15;
    int alfa = 90;
    float ipotenusa, perimetro, altezza, area;

    printf("\n-------------------------------------\n");
    printf("Inserisci il valore del cateto minore: ");
    scanf("%f", &ac);

    printf("Inserisci il valore dell'angolo gamma: ");
    scanf("%f", &gamma);
    printf("\n-------------------------------------\n");

    calcolo_ipotenusa(&ac, &gamma, &ipotenusa);
    printf("L'ipotenusa del triangolo è: %f\n", ipotenusa);

    perimetro = calcolo_perimetro(ac, ipotenusa, &bc);
    printf("Il perimetro del triangolo è: %f\n", perimetro);

    calcolo_area(&perimetro, ac, &ipotenusa, &bc, &area);
    printf("L'area del triangolo è: %f\n", area);

    altezza = calcolo_altezza(&ipotenusa, &area);
    printf("L'altezza del triangolo è: %f\n", altezza);

    return 0;

}