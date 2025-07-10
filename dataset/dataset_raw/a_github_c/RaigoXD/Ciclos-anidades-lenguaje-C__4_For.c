
#include <stdio.h>

int main()
{
    int Mayor = 0;
    int menor = 0; 
    int Mayor_150 = 0; 
    int negativos = 0;
    float promedio_P = 0.0; 
    int contador = 1; 
    int num_p = 0;  
    for(contador = 0; contador < 10;)
    {
     int numero = 0;
        
     printf("\nIngrese por favor el numero: ");
     scanf("%i", &numero);
     if(numero != 0){
         if(numero > 150){
             ++Mayor_150;    
         }
         if(numero > Mayor){
             Mayor = numero;    
         }else if(numero < menor){
             menor = numero;    
         }

         if(numero > 0){
             ++num_p;
             promedio_P += numero; 
         }else{
             ++negativos;          
         }
         ++contador;
         }
     }
     printf("\n***Fin del Ciclo***\n");
     promedio_P = promedio_P / num_p;

     printf("\nCantidad de numeros mayores a 150: %i", Mayor_150);
     printf("\nNumero mayor: %i  Numero menor: %i", Mayor, menor);   
     printf("\nCantidad de numeros negativos encontrador: %i", negativos);
     printf("\nPromedio positivos encontrados: %f", promedio_P);
}

