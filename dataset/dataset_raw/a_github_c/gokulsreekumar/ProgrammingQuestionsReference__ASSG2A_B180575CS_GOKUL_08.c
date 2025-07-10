#include<stdio.h>
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


int check_digit(int n)
{
    int count=0;
    if(n==0)
        return 1;
    while(n>0)
    {
        n=n/10;
        count++;
    }
    return count;
}
int check_digit_array(int A[], int n)
{
    int s;
    int num = check_digit(A[0]);
    for(int i = 1; i<n; i++)
    {
        s = check_digit(A[i]);
        if(s != num)
            return 0;
    }
    return 1;
}


int getMax(int arr[], int n) {
    int mx = arr[0];
    int i;
    for (i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}
 
void countSort(int arr[], int n, int exp) {
    int output[n]; 
    int i, count[10] = { 0 };
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
 
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
 
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 
void radix_sort(int arr[], int n) {
    int m = getMax(arr, n);
 
    int exp;
    for (exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}
 
int main(int argc, char* argv[]) {
    
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
            int nm1 = check_digit_array(arr, 6);
            if(nm1 != 0)
            {
                radix_sort(arr, size);
        display(arr, size);
            }
        }

        else if(s == 'd')
        {
                display(arr, size);
                fprintf(F2, "\n");
        }
        else if(s == 't')
                return 0;
        }
    
        return 0;

}
