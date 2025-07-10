

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()

{
        int i,j,z;
    int a[5];
    int b[5];
    int c[5];



    for(i = 0; i < 5; i++){

        printf("Digite um valor para a: ", i);
        scanf("%d",&a[i]);

    }

        printf("\n \n");




    for(z = 0; z < 5; z++){

        if( z %2 ==0){

            c[z] = a[z];
        printf("\n vetor c(impar): %d \n",c[z]);
        }

         if( z %2 != 0){
            b[z] = a[z];

        printf("\n vetor b (par): %d \n",b[z]);
        }

    }




    system("PAUSE");
    return 0;
}
