
#include <stdio.h>

int ft_eight_queens_puzzle(void);
int Mov_Queen(int [8][8], int, int);


int main(){
    printf("%i", ft_eight_queens_puzzle());
}

int ft_eight_queens_puzzle(void){
    int Tabla[8][8] = {{0,0,0,0,0,0,0,0},     
                       {0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0},
                       {0,0,0,0,0,0,0,0}};
    int  contador = 0;

    for(int Col_0 = 0; Col_0 < 8; Col_0++){  
        Tabla[Col_0][0] = 1; 

        for(int Col_1 = 0; Col_1 < 8; Col_1++){ 
            if(Mov_Queen(Tabla, Col_1, 1) == 0){
               Tabla[Col_1][1] = 1; 

               for (int Col_2 = 0; Col_2 < 8; Col_2++){ 
                   if(Mov_Queen(Tabla, Col_2, 2) == 0){
                        Tabla[Col_2][2] = 1; 

                        for (int Col_3 = 0; Col_3 < 8; Col_3++){ 
                            if(Mov_Queen(Tabla, Col_3, 3) == 0){
                                Tabla[Col_3][3] = 1; 

                                for (int Col_4 = 0; Col_4 < 8; Col_4++){  
                                    if(Mov_Queen(Tabla, Col_4, 4) == 0){
                                        Tabla[Col_4][4] = 1; 

                                        for (int Col_5 = 0; Col_5 < 8; Col_5++){ 
                                            if(Mov_Queen(Tabla, Col_5, 5) == 0){
                                                Tabla[Col_5][5] = 1; 

                                                for (int Col_6 = 0; Col_6 < 8; Col_6++){ 
                                                    if(Mov_Queen(Tabla, Col_6, 6) == 0){
                                                        Tabla[Col_6][6] = 1; 

                                                        for (int Col_7 = 0; Col_7 < 8; Col_7++) 
                                                        {
                                                            if(Mov_Queen(Tabla, Col_7, 7) == 0){
                                                                Tabla[Col_7][7] = 1; 
                                                                contador++;
                                                            }
                                                            Tabla[Col_7][7] = 0;  
                                                        }
                                                    }
                                                    Tabla[Col_6][6] = 0;
                                                }
                                            }
                                            Tabla[Col_5][5] = 0;
                                        }  
                                    } 
                                    Tabla[Col_4][4] = 0;
                                }
                            }
                            Tabla[Col_3][3] = 0;
                        }
                    }
                    Tabla[Col_2][2] = 0; 
                }
            }
            Tabla[Col_1][1] = 0;
        }
        Tabla[Col_0][0] = 0;
    }
    return contador; 
}


int Mov_Queen(int Tabla[8][8], int fila, int columna){   
                                                         
    int fila_actual = 0; 
    int columna_actual = 0; 
    int estado = 0; 
    
    for(int i = columna + 1; i < 8; i++) 
        if(Tabla[fila][i] == 1)
            estado = 1;
    
    for(int i = columna - 1; i >= 0; i--) 
       if(Tabla[fila][i] == 1)
            estado = 1; 

    for(int i = fila - 1; i >= 0; i--) 
       if(Tabla[i][columna] == 1)
            estado = 1; 

    for(int i = fila + 1; i < 8; i++) 
       if(Tabla[i][columna] == 1)
            estado = 1;

    fila_actual = fila - 1;
    columna_actual = columna + 1;
    while(columna_actual < 8 && fila_actual >= 0){    
        if(Tabla[fila_actual][columna_actual] == 1)
            estado = 1;
        fila_actual--;
        columna_actual++;
    }

    fila_actual = fila - 1;
    columna_actual = columna - 1;
    while(columna_actual >= 0 && fila_actual >= 0){    
        if(Tabla[fila_actual][columna_actual] == 1)
            estado = 1;
        fila_actual--;
        columna_actual--;
    }

    fila_actual = fila + 1;
    columna_actual = columna - 1;
    while(columna_actual >= 0 && fila_actual < 8){    
        if(Tabla[fila_actual][columna_actual] == 1)
            estado = 1;
        fila_actual++;
        columna_actual--;
    }

    fila_actual = fila + 1;
    columna_actual = columna + 1;
    while(columna_actual < 8 && fila_actual < 8){    
        if(Tabla[fila_actual][columna_actual] == 1)
            estado = 1;
        fila_actual++;
        columna_actual++;
    }
    return estado;
}