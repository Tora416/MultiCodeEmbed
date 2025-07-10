#include<stdio.h>

int main(){
  int dim;
  int check = 0;

  
  printf("dammi dim: ");
  scanf("%d", &dim);

  int arr[dim];

  printf("riempi array arr.\n");
  for(int i = 0; i < dim; i++){
    printf("dammi un numero: ");
    scanf("%d", &arr[i]);
  }

  for(int i = 0; i < dim; i++){
  if(arr[i] != arr[dim - i - 1]){
      check = 1;
      i = dim; 
    }
  }


  if(check == 0){
    printf("la sequenza è palindroma.\n");
  }else{
    printf("la sequenza non è palindroma.\n");
  }

  return(0);
}