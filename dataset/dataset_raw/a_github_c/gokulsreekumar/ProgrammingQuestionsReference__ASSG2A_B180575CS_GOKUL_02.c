#include <stdio.h>
#include <stdlib.h>


FILE* F1;
FILE* F2;

int search_shift(int a[],int n)
{
    int str = 0;
    int end = n-1;
    int mid = (end + str)/2;
    if(a[n-1] > a[str])
    {
        return 0;
    }
    while(end>str)
    {
        mid = (end+str)/2;
        if(a[mid-1]> a[mid]){
            return mid;
        }
        else if(a[mid-1]<=a[mid] && a[mid]<=a[end])
        {
            end = mid;
        }
        else if(a[mid - 1]<= a[mid] && a[mid]>=a[end])
        {
            str = mid;
        }
    }
    return 0;
        
}
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

int main(int argc, char* argv[])
{
    int search_shift(int a[], int);
    int num; char s;int size;
        int* arr;
        F1 = fopen(argv[1], "r");
        F2 = fopen(argv[2], "w");
        while(1)
        {
        fscanf(F1 ,"%c",&s);
        if(s == 'r')
        {
        fscanf(F1, "%d", &num);
                size = num;
                arr = read(num);

        }
        else if(s == 's')
        {
                int p = search_shift(arr, size);
                fprintf(F2,"%d\n", p);
        }

        else if(s == 'd')
        {
                display(arr, size);
                fprintf(F2, "\n");
        }
    else if(s == 't')
        return 0;
    }
    fclose(F1);
    fclose(F2);
}
