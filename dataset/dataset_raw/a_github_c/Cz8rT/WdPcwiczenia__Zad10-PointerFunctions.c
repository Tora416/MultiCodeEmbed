#include <stdio.h>
#define MIESIACE 12
#define LATA 5

void printAvgYear(float pointer[][0]);
void printAvgMonth(float apointer[][0]);

int main()
{
    const float deszcz[LATA][MIESIACE] = {
        {10.2, 8.1, 6.8, 4.2, 2.1, 1.8, 0.2, 0.3, 1.1, 2.3, 6.1, 7.4},
        {9.2, 9.8, 4.8, 3.2, 2.5, 4.8, 1.2, 0.5, 1.6, 1.3, 7.1, 7.4},
        {10.6, 5.6, 6.7, 4.4, 3.8, 1.8, 2.2, 7.3, 2.6, 4.3, 4.6, 4.6},
        {12.5, 3.7, 4.3, 0.2, 2.1, 1.7, 4.6, 0.5, 1.6, 0.3, 9.1, 2.4},
        {12.2, 9.1, 7.8, 1.2, 8.4, 1.5, 0.2, 3.5, 3.8, 1.3, 7.1, 4.4}
    };

    printAvgYear(deszcz);
    printAvgMonth(deszcz);

    printf("\n");
    return 0;
}

void printAvgYear(float pointer[][0]){
    float * rok;        
    float * miesiac;    
    float podsuma, suma;
    int licznik = 0;

    for(rok = *pointer, suma = 0; rok <= *pointer + 48; rok = rok + 12){
        for(miesiac = *pointer + (12*licznik) , podsuma = 0; miesiac <= *pointer + 11 + (12*licznik); miesiac++){
            podsuma += *miesiac;
        }
        printf("%5d %12.1f\n", 1995 + licznik, podsuma);
        licznik++;
        suma += podsuma;
    }

    printf("\nRoczna srednia wynosi %.1f cm.\n\n", suma/LATA);
}

void printAvgMonth(float pointer[][0]){
    float * rok;        
    float * miesiac;    
    float podsuma, suma;

    printf("SREDNIE MIESIECZNE:\n\n");
    printf(" Sty  Lut  Mar  Kwi  Maj  Cze  Lip  Sie  Wrz  Paz ");
    printf(" Lis  Gru\n");

    for (miesiac = *pointer; miesiac <= *pointer + 11; miesiac++){
        for(rok = miesiac, podsuma = 0; rok <= *pointer + 48 + 11; rok = rok + 12){ 
            podsuma += *rok;
        }
        printf("%4.1f ", podsuma/LATA);
    }
}
