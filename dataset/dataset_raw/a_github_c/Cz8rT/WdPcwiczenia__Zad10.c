#include <stdio.h>
#include <stdlib.h>

int main()
{
    float a, c, x1, x2, delta;

    printf("Prosz\251 poda\206 warto\230\206 wsp\242\210czynnika a: ");
    scanf("%f", &a);
    printf("Prosz\251 poda\206 warto\230\206 wsp\242\210czynnika c: ");
    scanf("%f", &c);

    delta = (2*2) - 4*3*a*c;

    if(a == 0){
        printf("\n'a' = 0!. Pierwiastek wynosi:");
        x1 = (-3*c)/2;
        printf("\nX1= %.2f\n", x1);
    }else if(delta < 0){
        printf("Rownanie nie ma rozwiazan.");
    } else {
        x1 = (-2-sqrt(delta))/(2*a);
        x2 = (-2+sqrt(delta))/(2*a);
        printf("\nX1= %.2f\n", x1);
        printf("X1= %.2f\n", x2);
    }

    printf("\n");
    return 0;
}
