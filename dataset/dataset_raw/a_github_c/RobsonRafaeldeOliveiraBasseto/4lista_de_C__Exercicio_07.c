
#include <stdio.h>
#include <stdlib.h>

int main()
{

     int i, maior, menor,posmaior,x;
     int vet[10];
    for (i = 0 ; i < 10 ; i++){
        printf("Digite o valor:\n");
        scanf("%d",&vet[i]);

    }
    maior=vet[0];
    posmaior=0;
    for (i=1;i<10;i++){
        if(vet[i]>maior){
            maior=vet[i];
            posmaior=i;
        }
    }
    menor=vet[0];
    for(i=1;i<10;i++){
    if(vet[i]<menor){
    menor=vet[i];
        }
    }
         printf("vetor: ");
    for (i = 0 ; i < 10 ; i++){

        printf("%d ",vet[i]);

    }
    printf("\nO maior valor eh: %d \n ",maior);
    printf("Posicao: %d\n",posmaior);



    return 0;
}
