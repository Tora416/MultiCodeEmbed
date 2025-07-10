#include <stdio.h>
#include <stdlib.h>

void scambia(int v[], int dim, int i, int j){

    if(dim > 0)
    {
        if((i > 0) && (i <= dim-1) && (j > 0) && (j <= dim-1))
        {
            int tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
        }
    }

}

void scambiaEsplicito(int v[], int dim, int i, int j){

    if(dim > 0)
    {
        if((i > 0) && (i <= dim-1) && (j > 0) && (j <= dim-1))
        {
            int tmp = *(v + i);
            *(v + i) = *(v + j);
            *(v + j) = tmp;
        }
    }

}

int main(void) {

    


  return 0;
}