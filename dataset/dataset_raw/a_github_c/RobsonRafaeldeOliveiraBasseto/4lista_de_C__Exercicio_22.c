

#include <stdio.h>
#include <stdlib.h>

int main()

{
    int i,j,z;
    int a[3];
    int b[3];
    int c[3];



    for(i = 0; i < 3; i++){

        printf("Digite um valor para a: ", i);
        scanf("%d",&a[i]);

    }

        printf("\n \n");

    for(j = 0; j < 3; j++){

        printf("Digite um valor para b: ", j);
        scanf("%d",&b[j]);

    }


    for(i = 0; i < 3; i++){
    printf("\n vetor a:  %d \n ", a[i]);
    }

    for(j = 0; j < 3; j++){
    printf("\n vetor b: %d \n ", b[j]);
    }


    for(z = 0; z < 3; z++){

        if( z %2 ==0){

            c[z] = a[z];
        }

        else if( z %2 != 0){
            c[z] = b[z];

        }

        printf("\n vetor c: %d \n",c[z]);
    }




    system("PAUSE");
    return 0;
}
