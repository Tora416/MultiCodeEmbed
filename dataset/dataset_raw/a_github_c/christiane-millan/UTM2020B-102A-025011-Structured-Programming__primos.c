#include <stdio.h>
#include <math.h>

int es_primo(int numero);

int main(){
    
    
    
    

    int primos = 0, no_primos = 0;
    for (int numero = 1; numero <= 10000; numero++)
    {   
        if(es_primo(numero)==1){
            
            primos++;
        } else {
            
            no_primos++;
        }
    }
    printf("Numero de primos %d, numero no primos %d", primos, no_primos);

    return 0;
}



int es_primo(int numero){
    for (int i = 2; i <= sqrt(numero); i++){
        if ( numero % i == 0) {
            return 0;
        }
    }
    return 1;
}