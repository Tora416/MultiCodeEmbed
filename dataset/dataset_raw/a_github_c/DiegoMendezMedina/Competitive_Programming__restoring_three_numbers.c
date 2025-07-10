#include <stdio.h>



void change(int vector[],int i, int j);
void quicksort(int vector[],int inf, int sup);

int main(){
  int x[4];
  int a,b,c;
  
  for(int i = 0; i < 4; i++)
    scanf("%d", &x[i]);

  quicksort(x, 0, 3);

  b = (x[2] - x[1] + x[0]) / 2;
  a = x[2] - b;
  c = x[0]- b;
  printf("%d %d %d\n", a, b, c);

}

void change(int vector[], int i, int j){
  int aux;
  
  aux = vector[i];
  vector[i] = vector[j];
  vector[j] = aux;
}


void quicksort(int vector[], int inf, int sup){
  int i, j, x;
  
  i = inf;
  j = sup;
  x = vector[(i+j)/2];
  
  while(i <= j){ 
      while(vector[i] < x)    
    i++;
      while(vector[j] > x)  
    j--;
      if(i<=j){
    change(vector, i, j);
    i++;
    j--;
      }
  }
  
  if(inf < j)
    quicksort(vector, inf, j);
  if(i < sup)
    quicksort(vector, i, sup);
}

