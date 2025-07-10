#include <stdio.h>
 


int get_numbers(int n, int max, int ns[], int i);
void imprime(int ns[]);
int check_number(int n, int ns[], int i);
int valid_array(int ns[], int x);
void quicksort(int vector[], int inf, int sup);
void change(int vector[], int i, int j);
  
int main(){
  int t, x;

  scanf("%d", &t);

  for(int i = 1; i <= t; i++){
    int numbers[9] = {0};
    
    scanf("%d", &x);
    
    if(x < 10)
      printf("%d\n", x);
    
    else{
      
      if(x > 45)
        printf("-%d\n", 1);
      
      else{
    get_numbers(x, 9, numbers, 0);
    quicksort(numbers, 0, 9);
    imprime(numbers);
    }
    }
  }
 
}


int get_numbers(int n, int max, int ns[], int i){
  int r = n - max;
  int check;

  if(i == 10)
    return 0;

  if(r < 10 && check_number(r, ns, i)){
    ns[i] = max;
    i++;
    if(check_number(r, ns, i)){
    ns[i] = r;
    return 1;
      }
    else{
      check = get_numbers(r, max-1, ns, i);
    }
  }
  else{
    ns[i] = max;
    i++;
    check = get_numbers(r, max-1, ns, i);
  }
  return (max == 9)? valid_array(ns, n): check;
}


int check_number(int n, int ns[], int i){
  for(int j = 0; j <= i; j++)
    if( n == ns[j])
      return 0;
  return 1;
}



int valid_array(int ns[], int x){
  int sum;

  sum = 0;
  for(int i = 0; i < 9; i++)
    sum += ns[i];
  return (sum == x)? 1 : 0;
}


void imprime(int ns[]){
  for(int i = 0; i < 9; i++)
    if(ns[i] != 0)
      printf("%d", ns[i]);
  printf("\n");
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
