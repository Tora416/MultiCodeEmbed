#include <stdio.h> 
#include<stdlib.h>

FILE* F1;
FILE* F2;
int* read(int n)
{
        int i;
        int s = sizeof(int);
        int* arr1= (int*)malloc(s * n);
        for(i = 0; i<n; i++)
        {
                fscanf(F1, "%d", (arr1+i));
        }
        return arr1;
}



void display(int arr2[], int n)
{
        int i;
        for(i = 0; i<n; i++)
        {
                fprintf(F2, "%d ", arr2[i]);
        }

}


void swap(int *a, int *b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 
  
void bubbleSort(int arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
       for (j = 0; j < n-i-1; j++)
    { 
       if(arr[j]>=0 && arr[j+1]>=0)
       {
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]);
       } 
       else if(arr[j]>0 && arr[j+1]<0)
       {
          for(int m = 0; m<n-j; m++)
          {
            if(arr[j+m]<arr[j] && arr[j+m]>=0)
            {
              swap(&arr[j+m], &arr[j]);
              break;
            }
          }
       }
       else if(arr[j]<0)
          continue;
   }
} 


int main(int argc, char* argv[]) 
{ 
    int num; char s;int size;
        int* arr;
        F1 = fopen(argv[1], "r");
        F2 = fopen(argv[2], "w");
        while(1)
        {
        fscanf(F1 ,"%c %d",&s, &num);
        if(s == 'r')
        {
                size = num;
                arr = read(num);

        }
        else if(s == 's')
        {
                bubbleSort(arr, size);
        display(arr, size);
        }

        else if(s == 'd')
        {
                display(arr, size);
                fprintf(F2, "\n");
        }
        else if(s == 't')
                return 0;
        }
} 
