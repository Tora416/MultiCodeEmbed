

#include <stdio.h>
#include <stdlib.h>

int main()

{

    int vetor[50];
    int i;


    for(i= 0; i < 50; i++){

        if(i %7 != 0 && i % 10 != 7 ){
            printf("\n %d \n", i);

        }


        else{
            continue;
        }
    }



    system("PAUSE");
    return 0;
}
