#include <stdio.h>
#include <stdlib.h>

void do_binar(int n, int sys);

int main()
{
    int liczba;
    int systemLiczbowy;

    printf("Podaj liczb\251 ca\210kowit\245 (q ko\344czy program):\n");

    while(scanf("%d", &liczba) == 1){
        printf("Podaj system liczbowy z zakresu od 2 do 10:\n");
        scanf("%d", &systemLiczbowy);
        printf("Odpowiednik w podanym systemie: ");
        do_binar(liczba, systemLiczbowy);
        putchar('\n');
        printf("Podaj liczb\251 ca\210kowit\245 (q ko\344czy program):\n");
    }
    return 0;
}

void do_binar(int n, int sys){
    int r;
    if(sys < 2 || sys > 10){
        printf("Podano system liczbowy spoza zakresu!!!");
        return;
    }

    r = n % sys;
    if(n >= sys)
        do_binar(n / sys, sys);
    putchar('0' + r);
    return;
}
