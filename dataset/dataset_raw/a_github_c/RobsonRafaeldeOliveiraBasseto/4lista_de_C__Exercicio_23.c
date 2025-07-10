

#include <stdio.h>
#include <stdlib.h>

int main()

{

    int i,j,z;
    int conjunto1[5];
    int conjunto2[5];


    for(i = 0; i < 5; i++){

        printf("Digite um valor para a: ", i);
        scanf("%d",&conjunto1[i]);

    }

        printf("\n \n");

    for(j = 0; j < 5; j++){

        printf("Digite um valor para b: ", j);
        scanf("%d",&conjunto2[j]);

    }



        int produto = 0;

       for (int i = 0; i < 5; i++){

       produto = produto + conjunto1[i] * conjunto2[i];


        }

        printf(" \n produto escalar dos dois conjuntos eh: %d \n", produto);

    system("PAUSE");
    return 0;
}
