#include <stdio.h>
#include <stdlib.h>

int czyTrojkat(float a, float b, float c);

int main()
{
    float first, second, third;

    printf("Podaj 1 bok: ");
    scanf("%f", &first);
    printf("Podaj 2 bok: ");
    scanf("%f", &second);
    printf("Podaj 3 bok: ");
    scanf("%f", &third);

    if(!czyTrojkat(first, second, third)){
        printf("Podane boki nie moga utworzyc trojkata!");
    } else {
        printf("Podane boki tworza piekny trojkat!");
    };

    printf("\n");
    return 0;
}

int czyTrojkat(float a, float b, float c){
    float max;
    float middle;
    float min;

    if(a <= 0 || b <= 0 || c <= 0){
        return 0;
    }

    if(a >= b && a >= c ) {
        max = a;
        if(b >= c) {
            min = c;
            middle = b;
        } else {
            min = b;
            middle = c;
        }
    } else if ( b >= c) {
        max = b;
        if(a >= c) {
             min = c;
             middle = b;
        } else {
             min = a;
             middle = c;
        }
    } else {
        max = c;
        if(a >= b) {
             min = b;
             middle = a;
        } else {
             min = a;
             middle = b;
        }
    }
    if(min + middle <= max){
        return 0;
    }
    return 1;
}
