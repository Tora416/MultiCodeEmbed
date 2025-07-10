#include <stdio.h>
#include <stdlib.h>


int main() {

    int primo;
    int a;
    int b;
    int c;


    printf("Digite um numero: ");
    scanf("%d", &a);



    for (b=a; ; b++) {


        primo = 1;
        for (c=2; c<b; c++) {

            if (b % c == 0)
                primo = 0;
}

                if (primo == 1) {
            printf("\n\nO numero a direita primo mais proximo: %d\n", b);
            break;
        }
    }




    for (b=a;b > 0; b--) {


        primo = 1;
        for (c=2; c<b; c++) {

            if (b % c == 0)
                primo = 0;
}

                if (primo == 1) {
            printf("O numero a esquerda primo mais proximo: %d\n", b);
            break;
        }
    }


}
