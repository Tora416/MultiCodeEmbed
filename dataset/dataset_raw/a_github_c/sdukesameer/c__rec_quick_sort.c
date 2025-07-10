#include<stdio.h>
#include<stdlib.h>
int n;
static int c=1;
void printArray(int arr[])
{
    int i;
    for (i=0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int partition (int arr[], int low, int high)
{
    int pivot = high;
    int i = low,j=high;
    while (i < j) {
        while (arr[i] < arr[pivot] && i <= high)
            i++;
        while (arr[j] >= arr[pivot] && j >= low)
            j--;
        if(i<j)
            swap(&arr[i],&arr[j]);
    }
    swap(&arr[i],&arr[pivot]);
    return (i);
}
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        printf("%d: ",c++);
        printArray(arr);
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
int main()
{
    
    scanf("%d",&n);
    if(n<1||n>50)
    {
        printf("ERROR");
        exit(1);
    }
    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d",&arr[i]);
    printf("Original: ");
    printArray(arr);
    printf("%d: ",c++);
    printArray(arr);
    quickSort(arr, 0, n-1);
    printf("Sorted: ");
    printArray(arr);
    return 0;
}