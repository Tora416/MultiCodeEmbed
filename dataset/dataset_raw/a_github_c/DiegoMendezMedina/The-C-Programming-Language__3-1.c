#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int binsearchv2(int x, int v[], int n);
int binsearch(int x, int v[], int n);
void selection_sort(int a[], int n);
void change(int a[], int b, int c);

int main(){
  int x, r, rv2, n;
  clock_t start, end;
  double time;

  printf("Size of the array\n");
  scanf("%d", &n);
  int array[n];
  
  for(int i = 0; i < n; i++)
    array[i] = rand() % n+1;
  selection_sort(array, n);
  
  printf("============================\n");
  for(int i = 0; i < n; i++)
    printf("%d ", array[i]);
  printf("\n============================\n");
  
  printf("\nNumber you're looking for: ");
  scanf("%d", &x);

  start = clock();
  r = binsearch(x, array, n);
  r == -1 ? printf("\n%d was not found\n", x) : printf("\n%d was found on %d\n", x, r);
  end = clock();
  time = (double) (end-start)/ CLOCKS_PER_SEC;
  printf("On an array of %d elements, binsearch takes: %f segs\n", n, time);

  start = clock();
  rv2 = binsearchv2(x, array, n);
  rv2 == -1 ? printf("\n%d was not found\n", x) : printf("\n%d was found on %d\n", x, rv2);
  end = clock();
  time = (double) (end-start)/ CLOCKS_PER_SEC;
  printf("On an array of %d elements, binsearchV2 takes: %f segs\n", n, time);
}


int binsearch(int x, int v[], int n){
  int low, high, mid;
  
  low = 0;
  high = n-1;
  while(low <= high){
    mid = (low+high) /2;
    if(x < v[mid])
      high = mid - 1;
    else if(x > v[mid])
      low = mid + 1;
    else 
      return mid;
  }
  return -1; 
}



int binsearchv2(int x, int v[], int n){
  int low, high, mid;
  
  low = 0;
  high = n-1;
  while(low < high){
    mid = (low+high)/2;
    if(x < v[mid])
      high = mid-1;
    else
      low = mid+1;
  }

  
  if(v[low-1] == x)
    return low-1;
  else if(v[low] == x)
    return low;
  else if(v[low+1] == x)
    return low+1;
  
  return -1; 
}

void selection_sort(int a[], int n){
  int smallest;
  int k;
  
  for(int i = 0; i < n - 1; i++){
    smallest = a[i];
    k = i;
    for(int j = i+1; j < n; j++)
      if(a[j] < smallest){
    smallest = a[j];
    k = j;
      }
    if(i != k)
      change(a, i, k);
  }
}

void change(int a[], int b, int c){
  int aux = a[b];
  a[b] = a[c];
  a[c] = aux;
}
