#include<stdio.h>
#include <stdlib.h>
int max(int* arr, int n){
    int m=0;
    for (int i = 0; i < n; i++){
        if(arr[i]>m)
            m=arr[i];
    }
    return m;
}
int min(int* arr, int n){
    int m=arr[0];
    for (int i = 0; i < n; i++){
        if(arr[i]<m)
            m=arr[i];
    }
    return m;
}
int main(){
    int n;
    int* arr;
    printf("Enter the size of the dynamic array: ");
    scanf("%d",&n);
    arr=(int*) malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++){
        printf("Enter the %dth element: ",i+1);
        scanf("%d",&arr[i]);
    }
    printf("\nMaximum Element = %d\n",max(arr,n));
    printf("Minimum Element = %d\n",min(arr,n));
}