

#include<stdio.h>
void comb(int, int, int, int *);
void comb(int i, int j,int k, int *datos){
    if( i <= 7){
        if(j <= 8){
            if(k <= 9 ){
                if(datos[i] != datos[j] && datos[i] != datos[k] && datos[j] != datos[k]){
                    if(datos[i] < datos[j] && datos[i] < datos[k] && datos[j] < datos[k]){
                        printf("%i%i%i  ", datos[i], datos[j], datos[k]);
                    }               
                }
                comb(i, j, k+1, datos);
            }else
                comb(i, j+1, 2, datos);
        }else
           comb(i+1, 1, k, datos);
    }
}


void ft_print_comb(); 
void ft_print_comb(){
    int datos[10] = {0,1,2,3,4,5,6,7,8,9};
    comb(0, 1,2, datos);
    
}

int main(){
    ft_print_comb(); 
    return 0;
}