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


void sort(int a[], int n)
{
    int i = 1;
    int shift, cmp;
    for(i = 1; i<n; i++)
    {
        int key = a[i];
        int j = i-1;
        cmp = 0;shift = 0;
        while(j>=0 && a[j]<key)
        {
            a[j+1]= a[j];
            j = j-1;
            cmp++;
            shift++;
        }
            a[j+1] = key;
            if(j != -1)
            {
                cmp++;
            }
            if( j != i-1)
            {
                shift++;
            }
            fprintf(F2, "%d %d\n", cmp, shift);
            display(a, n);
            fprintf(F2, "\n");

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
                sort(arr, size);
        }

        else if(s == 'd')
        {
                display(arr, num);
                fprintf(F2, "\n");
        }
        else if(s == 't')
                return 0;
        }
        fclose(F1);
        fclose(F2);
    
}

