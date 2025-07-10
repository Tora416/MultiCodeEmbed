
  
#include <stdio.h>
#include <stdlib.h>




void bresenham1(int x1, int y1, int x2, int y2){        
        int slope;
        int dx, dy, incE, incNE, d, x, y; 
        if (x1 > x2 && y1 > y2){
            bresenham1(x2, y2, x1, y1);
             return;
        }        
        dx = x2 - x1;
        dy = y2 - y1;
    
        if (dy < 0){            
            slope = -1;
            dy = -dy;
        }
        else{            
           slope = 1;
        }
  
        incE = 2 * dy;
        incNE = 2 * dy - 2 * dx;
        d = 2 * dy - dx;
        y = y1;
        
    printf("dx = %d\n", dx);
    printf("dy = %d\n",dy);
    printf("2dy = %d\n",incE);
    printf("2dy-2dx %d\n",incNE);

    int tam;
    if (x2 - x1 > 0){
        tam = x2 - x1;
    }
    else if(x2-x1==0){
        tam = y2-y1;
    }
    else{
        tam = -(x2 - x1);
    }

    int vecX[tam];
    int vecY[tam];
    int vecPk[tam];
    
    int i =0;
        
        
        if(x2-x1 == 0){
            while(y1 < y2){
                if (d < 0){
                  d = d + incE;
                }
                else{
                  d = d + incNE;
                  x = x + slope;
                }
                
                vecPk[i] = d;
                vecX[i] = x1;
                vecY[i] = y1;
                i++;
                y1++;
            }
            
        }else{
            while(x1 < x2){
                if (d < 0){
                  d = d + incE;
                }
                else{
                  d = d + incNE;
                  y = y + slope;
                }
                
            vecPk[i] = d;
            vecX[i] = x1;
            vecY[i] = y;
            i++;
            x1++;
            }
        }
        
    printf("X  | ");
    for (int i = 0; i < tam; i++)
    {
        printf("%d ", vecX[i]);
    }
    printf("\n");

    printf("Y  | ");
    for (int i = 0; i < tam; i++)
    {
        printf("%d ", vecY[i]);
    }
    printf("\n");

    printf("Pk | ");
    for (int i = 0; i < tam; i++)
    {
        printf("%d ", vecPk[i]);
    }
    printf("\n");
 }

void imprime(int *vec, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf("%d", vec[i]);
    }
}

int main(void)
{
    bresenham1(30,5,30,15);
    return 0;
}
