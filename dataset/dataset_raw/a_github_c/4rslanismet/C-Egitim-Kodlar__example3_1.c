

#include <stdio.h>

#define SIZE 11

void yaz (int arr[SIZE]);
int oku (int arr[SIZE]);


void main (void)
{
    int numara[SIZE];

    printf("%s,\n","okul numaranızı giriniz:");

    numara=oku(numara);
    
    

}


void yaz (int arr[SIZE])
{
    int i;
    
    for(i=0;i<SIZE;i++)
        printf("%d",arr[i]);

}


int oku (int arr[SIZE])
{
    int i;

    for(i=0;i<SIZE;i++)
        scanf("%d",&arr[i]);

    return arr;    
}