
#include <stdio.h>
#include <stdlib.h>

int main(void){
    long house_nr = 0, nr_presents = 0;

    while(1){
        
        for(long i = 1; i <= house_nr; i++){
            if(house_nr%i == 0){
                
                nr_presents += i * 10;
            }
        }

        
        if(nr_presents >= 33100000){
            printf("answer=%ld\n", house_nr);
            break;
        }

        if(house_nr%10000 == 0)
            printf("%ld - %ld\n", house_nr, nr_presents);
        house_nr++;
        nr_presents = 0;
    }

    return EXIT_SUCCESS;
}