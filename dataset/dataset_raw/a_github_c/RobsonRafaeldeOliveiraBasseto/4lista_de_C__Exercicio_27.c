

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()

{

    int vetor[5];
    int primos[5];
    int i,j;
    int c = 0;
    int t = 0;


        for(i = 0; i < 5; i++){


            printf("Digite um numero %d: ",i+1);
            scanf("%d",&vetor[i]);

        }

        for(i= 0; i < 5; i++){

            c = 0;



            for(j =2; j < vetor[i]; j++){

                if(vetor[i]%j == 0){
                    c=1;
                    break;
                }

            }

        if(c == 0){
            primos[t] = vetor[i];
            t++;
        }
    }

    printf("\n \n Numeros primos do array : \n \n");

    for(i =0; i < t; i++){
        printf("\n %d \n",primos[i]);
    }


    system("PAUSE");
    return 0;
}
