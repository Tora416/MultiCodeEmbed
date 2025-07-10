#include<stdio.h>
#include<stdlib.h>
#define MAX 50
int arr[MAX], n;
static int c=1;
void printArray()
{
    int i;
    for (i=0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
void merge_array(int a, int b, int c, int d) {
    int temp[n];
    int i = a, j = c, k = 0;
    while (i <= b && j <= d) {
        if (arr [i] < arr[j])
            temp[k++] = arr [i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= b)
        temp[k++] = arr[i++];
    while (j <= d)
        temp[k++] = arr[j++];
    for (i = a, j = 0; i <= d; i++, j++)
        arr[i] = temp[j];
}
void merge_sort(int i, int j) {
    int m;
    if (i < j) {
        m = (i + j) / 2;
        merge_sort(i, m);
        merge_sort(m + 1, j);
        merge_array(i, m, m + 1, j);
        printf("%d: ",c++);
        printArray();
    }
}
int main() {
    int i;
    scanf("%d",&n);
    if(n<1||n>50)
    {
        printf("ERROR");
        exit(1);
    }
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Original: ");
    printArray();
    merge_sort(0, n - 1);
    printf("Sorted: ");
    printArray();
    return 0;
}