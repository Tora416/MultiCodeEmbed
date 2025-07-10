

#include<stdio.h>

void ft_print_comb2(); 

void ft_print_comb2(){
    int x = 9;
    int m = 0;
    for(int i = 0; i<= 9; i++){
        if(i == 9)
            x = 8;
        for(int j = 0; j <= x; j++){
            for(int k = 0; k <= 9; k++){    
                if(j != 0)
                    m = 0;
                for(int l = m; l <= 9; l++){
                    if( i*10 + j != k*10+l){
                        printf("%i%i %i%i, ", i,j,k,l);
                    }
                }
            }
        }
    }
}

int main(){
    ft_print_comb2(); 
    return 0;
}